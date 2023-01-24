// Copyright (c) CD PROJEKT S.A.

#include "RedTalaria.h"

#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Styling/CoreStyle.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FRedTalariaModule"

const FName FRedTalariaModule::SlateStyleSetName = TEXT("RedTalariaModuleStyleSet");
const FName FRedTalariaModule::TalariaIconSlateStyleName = TEXT("RedTalariaModule_TalariaIcon");

const FString RedTalariaPluginName(TEXT("RedTalaria"));

void FRedTalariaModule::StartupModule()
{
	RegisterSlateStyle();
}

void FRedTalariaModule::ShutdownModule()
{
	UnregisterSlateStyle();
}

void FRedTalariaModule::RegisterSlateStyle()
{
	const auto Plugin = IPluginManager::Get().FindPlugin(RedTalariaPluginName);
	checkf(Plugin, TEXT("Couldn't load our own plugin descriptor"));

	SlateStyle = MakeShareable(new FSlateStyleSet(SlateStyleSetName));

	SlateStyle->SetContentRoot(FPaths::Combine(Plugin->GetContentDir(), TEXT("Editor/Slate")));

#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(SlateStyle->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#if ENGINE_MAJOR_VERSION >= 5
	SlateStyle->Set(TalariaIconSlateStyleName, new IMAGE_BRUSH("RedTalaria_16", CoreStyleConstants::Icon16x16));
#else
	const FVector2D Icon16X16(16.0f, 16.0f);
	SlateStyle->Set(TalariaIconSlateStyleName, new IMAGE_BRUSH("RedTalaria_16", Icon16X16));
#endif
#undef IMAGE_BRUSH

	FSlateStyleRegistry::RegisterSlateStyle(*SlateStyle);
}

void FRedTalariaModule::UnregisterSlateStyle()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlateStyle);
	SlateStyle.Reset();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRedTalariaModule, RedTalaria)
