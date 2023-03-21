// Copyright (c) CD PROJEKT S.A.

#include "RedHermesContentFolderEndpointModule.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FRedHermesContentFolderEndpointModule"

void FRedHermesContentFolderEndpointModule::StartupModule()
{
}

void FRedHermesContentFolderEndpointModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRedHermesContentFolderEndpointModule, RedHermesContentFolderEndpoint)
