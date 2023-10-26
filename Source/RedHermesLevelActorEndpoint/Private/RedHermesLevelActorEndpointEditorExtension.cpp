// Copyright (c) CD PROJEKT S.A.

#include "RedHermesLevelActorEndpointEditorExtension.h"

#include "LevelEditor.h"
#include "RedTalaria.h"
#include "RedTalariaLevelActorUrls.h"
#include "ToolMenus.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Runtime/Launch/Resources/Version.h"

#define LOCTEXT_NAMESPACE "Editor.RedHermesLevelActorEndpointEditorExtension"

const FName LevelEditorModuleName(TEXT("LevelEditor"));

void URedHermesLevelActorEndpointEditorExtension::Initialize(FSubsystemCollectionBase& Collection)
{
	RegisterExtender();
}

void URedHermesLevelActorEndpointEditorExtension::Deinitialize()
{
	UnregisterExtender();
}

void URedHermesLevelActorEndpointEditorExtension::RegisterExtender()
{
	auto& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>(LevelEditorModuleName);
	LevelEditorModule.GetAllLevelViewportContextMenuExtenders().Add(
		FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateStatic(&ThisClass::HandleOnExtendLevelEditorActorContextMenu));
}

void URedHermesLevelActorEndpointEditorExtension::UnregisterExtender()
{
	if (auto* LevelEditorModule = FModuleManager::GetModulePtr<FLevelEditorModule>(LevelEditorModuleName))
	{
		LevelEditorModule->GetAllLevelViewportContextMenuExtenders().RemoveAll(
			[](const FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors& Delegate) {
				const FName LocalFunction = GET_FUNCTION_NAME_CHECKED(ThisClass, HandleOnExtendLevelEditorActorContextMenu);
				return Delegate.TryGetBoundFunctionName() == LocalFunction;
			});
	}
}

TSharedRef<FExtender> URedHermesLevelActorEndpointEditorExtension::HandleOnExtendLevelEditorActorContextMenu(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> SelectedActors)
{
	TSharedRef<FExtender> Extender(new FExtender());

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	if (!SelectedActors.IsEmpty())
	{
		TArray<FString> ActorUrls;
		Algo::TransformIf(
			SelectedActors, ActorUrls,
			[](const AActor* Actor) {
				return (Actor != nullptr) && Actor->IsPackageExternal();
			},
			[](const AActor* Actor) {
				return FRedTalariaLevelActorUrls::GetUrlForLevelActor(Actor->GetPackage()->GetFName(), Actor->GetActorNameOrLabel());
			});
		FString URlsToCopy = FString::Join(ActorUrls, TEXT("\n"));

		Extender->AddMenuExtension(
			TEXT("ActorOptions"),
			EExtensionHook::Before,
			CommandList,
			FMenuExtensionDelegate::CreateStatic(&ThisClass::HandleOnExtendContextMenu, MoveTemp(URlsToCopy)));
	}
#endif

	return Extender;
}

void URedHermesLevelActorEndpointEditorExtension::HandleOnExtendContextMenu(FMenuBuilder& MenuBuilder, FString UrlsToCopy)
{
	if (UrlsToCopy.IsEmpty())
	{
		return;
	}

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("SectionName", "Hermes"));
	MenuBuilder.AddMenuEntry(
		LOCTEXT("ActorAction.CopyHermesUrl", "Copy selected actor URL(s)"),
		LOCTEXT("ActorAction.CopyHermesUrlTooltip", "Copy an URL (for each selected actor) that will open this level and focus on that actor."),
		FSlateIcon(FRedTalariaModule::SlateStyleSetName, FRedTalariaModule::TalariaIconSlateStyleName),
		FUIAction(FExecuteAction::CreateLambda([UrlsToCopy]() {
			FPlatformApplicationMisc::ClipboardCopy(*UrlsToCopy);
		})));
	MenuBuilder.EndSection();
}
