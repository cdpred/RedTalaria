// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Templates/SharedPointer.h"
#include "UObject/NameTypes.h"

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
