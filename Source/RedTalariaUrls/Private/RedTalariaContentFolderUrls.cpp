// Copyright (c) CD PROJEKT S.A.

#include "RedTalariaContentFolderUrls.h"

#include "HermesServer.h"
#include "Modules/ModuleManager.h"

const FName FRedTalariaContentFolderUrls::HermesEndpointId = TEXT("content_folder");

FString FRedTalariaContentFolderUrls::GetUrlForContentFolder(FName FolderPath)
{
	if (const auto Hermes = FModuleManager::LoadModulePtr<IHermesServerModule>(TEXT("HermesServer")))
	{
		return Hermes->GetUri(HermesEndpointId, *FolderPath.ToString());
	}

	return FString(TEXT(""));
}
