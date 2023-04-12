// Copyright (c) CD PROJEKT S.A.

#include "RedHermesGraphNodeEndpoint.h"

#include "RedTalariaGraphNodeUrls.h"
#include "AssetRegistry/AssetData.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Widgets/SWindow.h"

DEFINE_LOG_CATEGORY_STATIC(LogRedHermesGraphNodeEndpoint, Log, All);

FName URedHermesGraphNodeEndpoint::GetHermesEndpointId() const
{
	return FRedTalariaGraphNodeUrls::HermesEndpointId;
}

void URedHermesGraphNodeEndpoint::ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const
{
	if (!QueryParams.Contains(FRedTalariaGraphNodeUrls::GuidQueryParamName))
	{
		UE_LOG(LogRedHermesGraphNodeEndpoint, Error, TEXT("%s query param is missing."), *FRedTalariaGraphNodeUrls::GuidQueryParamName);
		return;
	}

	const FGuid NodeGuid(QueryParams[FRedTalariaGraphNodeUrls::GuidQueryParamName]);

	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	TArray<FAssetData> AssetData;
	AssetRegistry.GetAssetsByPackageName(*Path, AssetData);

	if (AssetData.Num() > 0)
	{
		OnRequestDelegate.Broadcast(NodeGuid, AssetData[0].GetAsset(), QueryParams.Contains(FRedTalariaGraphNodeUrls::OpenJumpTargetQueryParamName));

		const IMainFrameModule& MainFrameModule = IMainFrameModule::Get();
		const TSharedPtr<SWindow> ParentWindow = MainFrameModule.GetParentWindow();
		if (ParentWindow.IsValid())
		{
			ParentWindow->ShowWindow();
			ParentWindow->GetNativeWindow()->HACK_ForceToFront();
		}
	}
	else
	{
		UE_LOG(LogRedHermesGraphNodeEndpoint, Error, TEXT("Failed loading asset for path %s."), *Path);
	}
}
