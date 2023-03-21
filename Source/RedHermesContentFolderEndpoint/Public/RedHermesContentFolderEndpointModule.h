// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Modules/ModuleInterface.h"

class FRedHermesContentFolderEndpointModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
