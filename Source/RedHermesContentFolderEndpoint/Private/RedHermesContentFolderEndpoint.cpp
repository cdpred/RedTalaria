// Copyright (c) CD PROJEKT S.A.

#include "RedHermesContentFolderEndpoint.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "RedTalariaContentFolderUrls.h"

FName URedHermesContentFolderEndpoint::GetHermesEndpointId() const
{
	return FRedTalariaContentFolderUrls::HermesEndpointId;
}

void URedHermesContentFolderEndpoint::ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const
{
	IContentBrowserSingleton& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser").Get();
	ContentBrowser.SyncBrowserToFolders({Path});
}
