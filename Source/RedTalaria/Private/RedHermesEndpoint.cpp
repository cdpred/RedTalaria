// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedHermesEndpoint.h"

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION >= 5
#include "AssetRegistry/AssetRegistryModule.h"
#else
#include "AssetRegistryModule.h"
#endif

#define LOCTEXT_NAMESPACE "Editor.RedHermesEndpoint"

DEFINE_LOG_CATEGORY_STATIC(LogRedHermesEndpoint, Log, All);

void URedHermesEndpoint::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	if (AssetRegistry.IsLoadingAssets())
	{
		UE_LOG(LogRedHermesEndpoint, Verbose, TEXT("Asset registry is currently loading..."));
		AssetRegistry.OnFilesLoaded().AddUObject(this, &ThisClass::OnAssetRegistryFilesLoaded);
	}

	IHermesServerModule& Hermes = FModuleManager::LoadModuleChecked<IHermesServerModule>(TEXT("HermesServer"));
	Hermes.Register(GetHermesEndpointId(), FHermesOnRequest::CreateUObject(this, &ThisClass::OnHermesRequest));
}

void URedHermesEndpoint::Deinitialize()
{
	if (const auto Hermes = FModuleManager::GetModulePtr<IHermesServerModule>(TEXT("HermesServer")))
	{
		Hermes->Unregister(GetHermesEndpointId());
	}

	if (const auto AssetRegistry = FModuleManager::GetModulePtr<FAssetRegistryModule>(TEXT("AssetRegistry")))
	{
		AssetRegistry->Get().OnFilesLoaded().RemoveAll(this);
	}

	Super::Deinitialize();
}

void URedHermesEndpoint::OnAssetRegistryFilesLoaded()
{
	UE_LOG(LogRedHermesEndpoint, Verbose,
		TEXT("Finished loading asset registry, processing %d pending requests"), PendingRequests.Num());

	for (const FPendingRequest& Request : PendingRequests)
	{
		ProcessRequest(Request.Path, Request.Query);
	}
	PendingRequests.Empty();
}

void URedHermesEndpoint::OnHermesRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams)
{
	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	if (AssetRegistry.IsLoadingAssets())
	{
		UE_LOG(LogRedHermesEndpoint, Verbose,
			TEXT("Received request for %s while loading asset registry, putting in queue"), *Path);
		FPendingRequest& Request = PendingRequests.AddDefaulted_GetRef();
		Request.Path = Path;
		Request.Query = QueryParams;
	}
	else
	{
		ProcessRequest(Path, QueryParams);
	}
}

#undef LOCTEXT_NAMESPACE
