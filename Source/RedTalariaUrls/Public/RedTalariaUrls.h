// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Modules/ModuleInterface.h"

class FRedTalariaUrlsModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
