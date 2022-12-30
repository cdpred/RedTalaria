// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedHermesLevelAtCameraCoordsEndpointEditorExtension.h"

#include "LevelEditorMenuContext.h"
#include "LevelEditorViewport.h"
#include "RedTalaria.h"
#include "RedTalariaLevelAtCameraCoordsUrls.h"
#include "ToolMenus.h"
#include "HAL/PlatformApplicationMisc.h"

#define LOCTEXT_NAMESPACE "Editor.RedHermesLevelAtCameraCoordsEndpointEditorExtension"

void URedHermesLevelAtCameraCoordsEndpointEditorExtension::Initialize(FSubsystemCollectionBase& Collection)
{
	RegisterViewportOptionMenuExtender();
}

void URedHermesLevelAtCameraCoordsEndpointEditorExtension::Deinitialize()
{
	UnregisterViewportOptionMenuExtender();
}

void URedHermesLevelAtCameraCoordsEndpointEditorExtension::RegisterViewportOptionMenuExtender()
{
	FToolMenuOwnerScoped ToolMenuOwnerScoped(this);

	if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelViewportToolBar.Options"))
	{
		static auto GetPerspectiveLevelEditorViewportClient = [](const FToolMenuContext& MenuContext) -> FLevelEditorViewportClient* {
			ULevelViewportToolBarContext* Context = MenuContext.FindContext<ULevelViewportToolBarContext>();
			if (Context && Context->LevelViewportToolBarWidget.IsValid())
			{
				FLevelEditorViewportClient* ViewportClient = Context->GetLevelViewportClient();
				if (ViewportClient && ViewportClient->ViewportType == LVT_Perspective)
				{
					return ViewportClient;
				}
			}

			return nullptr;
		};

		FToolUIAction CopyLinkToLevelAtCameraCoordsAction;
		CopyLinkToLevelAtCameraCoordsAction.ExecuteAction.BindLambda([](const FToolMenuContext& MenuContext) {
			if (const FLevelEditorViewportClient* ViewportClient = GetPerspectiveLevelEditorViewportClient(MenuContext))
			{
				const FName LevelPackageName = ViewportClient->GetWorld()->GetPackage()->GetFName();
				const FVector Location = ViewportClient->GetViewLocation();
				const FRotator Rotation = ViewportClient->GetViewRotation();
				FPlatformApplicationMisc::ClipboardCopy(
					*FRedTalariaLevelAtCameraCoordsUrls::GetUrlForLevelAtLocationAtRotation(LevelPackageName, Location, Rotation));
			}
		});
		CopyLinkToLevelAtCameraCoordsAction.CanExecuteAction.BindLambda([](const FToolMenuContext& MenuContext) {
			return GetPerspectiveLevelEditorViewportClient(MenuContext) != nullptr;
		});

		FToolMenuSection& Section = Menu->AddSection(
			TEXT("Hermes"),
			LOCTEXT("LevelViewportToolBar.Options.Hermes", "Hermes"),
			FToolMenuInsert(TEXT("LevelViewportViewportOptions"), EToolMenuInsertType::Before));
		Section.AddMenuEntry("CopyURL",
			LOCTEXT("ViewportAction.CopyCameraCoordsUrl", "Copy camera coords URL"),
			LOCTEXT("ViewportAction.CopyCameraCoordsUrlTooltip", "Copy an URL that will open this level at the current camera position"),
			FSlateIcon(FRedTalariaModule::SlateStyleSetName, FRedTalariaModule::TalariaIconSlateStyleName),
			CopyLinkToLevelAtCameraCoordsAction);
	}
}

void URedHermesLevelAtCameraCoordsEndpointEditorExtension::UnregisterViewportOptionMenuExtender()
{
	UToolMenus::UnregisterOwner(this);
}

#undef LOCTEXT_NAMESPACE
