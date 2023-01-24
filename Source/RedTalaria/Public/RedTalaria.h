// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"

class FSlateStyleSet;

class REDTALARIA_API FRedTalariaModule : public IModuleInterface
{
public:
	static const FName SlateStyleSetName;
	static const FName TalariaIconSlateStyleName;

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr<FSlateStyleSet> SlateStyle;

	void RegisterSlateStyle();
	void UnregisterSlateStyle();
};
