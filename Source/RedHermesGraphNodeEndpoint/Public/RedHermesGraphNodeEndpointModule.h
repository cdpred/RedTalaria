// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Modules/ModuleInterface.h"

class FRedHermesGraphNodeEndpointModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
