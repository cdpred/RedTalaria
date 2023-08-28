// Copyright (c) CD PROJEKT S.A.

#include "RedTalariaContentUrls.h"

#include "HermesServer.h"
#include "Modules/ModuleManager.h"

const FName FRedTalariaContentUrls::HermesEndpointId = TEXT("content");

FString FRedTalariaContentUrls::GetUrlForPackage(FName PackageName)
{
	if (const auto Hermes = FModuleManager::LoadModulePtr<IHermesServerModule>(TEXT("HermesServer")))
	{
		return Hermes->GetUri(HermesEndpointId, *PackageName.ToString());
	}

	return FString();
}
