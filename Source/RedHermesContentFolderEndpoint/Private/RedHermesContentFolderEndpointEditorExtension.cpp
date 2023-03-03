// Copyright (c) CD PROJEKT S.A.

#include "RedHermesContentFolderEndpointEditorExtension.h"

#include "ContentBrowserMenuContexts.h"
#include "RedTalaria.h"
#include "RedTalariaContentFolderUrls.h"
#include "ToolMenus.h"
#include "HAL/PlatformApplicationMisc.h"

#define LOCTEXT_NAMESPACE "Editor.RedHermesContentFolderEndpointEditorExtension"

void URedHermesContentFolderEndpointEditorExtension::Initialize(FSubsystemCollectionBase& Collection)
{
	RegisterContentBrowserFolderContextExtender();
}

void URedHermesContentFolderEndpointEditorExtension::Deinitialize()
{
	UnregisterContentBrowserFolderContextExtender();
}

void URedHermesContentFolderEndpointEditorExtension::RegisterContentBrowserFolderContextExtender()
{
	FToolMenuOwnerScoped ToolMenuOwnerScoped(this);

	FToolUIAction CopyLinkToFolderAction;
	CopyLinkToFolderAction.ExecuteAction.BindLambda([](const FToolMenuContext& MenuContext) {
		if (const UContentBrowserDataMenuContext_FolderMenu* Context = GetContextWithSingleFolderSelected(MenuContext))
		{
			FPlatformApplicationMisc::ClipboardCopy(
				*FRedTalariaContentFolderUrls::GetUrlForContentFolder(Context->SelectedItems[0].GetInvariantPath()));
		}
	});
	CopyLinkToFolderAction.CanExecuteAction.BindLambda([](const FToolMenuContext& MenuContext) {
		return GetContextWithSingleFolderSelected(MenuContext) != nullptr;
	});

	if (UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.FolderContextMenu"))
	{
		FToolMenuSection& Section = Menu->AddSection(
			TEXT("Hermes"),
			LOCTEXT("ContentBrowser.FolderContextMenu.Hermes", "Hermes"));
		Section.AddMenuEntry("CopyURL",
			LOCTEXT("ContentBrowser.FolderContextMenu.CopyFolderUrl", "Copy folder URL"),
			LOCTEXT("ContentBrowser.FolderContextMenu.CopyFolderUrlTooltip", "Copy an URL that will reveal this folder in the content browser."),
			FSlateIcon(FRedTalariaModule::SlateStyleSetName, FRedTalariaModule::TalariaIconSlateStyleName),
			CopyLinkToFolderAction);
	}
}

void URedHermesContentFolderEndpointEditorExtension::UnregisterContentBrowserFolderContextExtender()
{
	UToolMenus::UnregisterOwner(this);
}

const UContentBrowserDataMenuContext_FolderMenu* URedHermesContentFolderEndpointEditorExtension::GetContextWithSingleFolderSelected(const FToolMenuContext& MenuContext)
{
	if (const auto* Context = MenuContext.FindContext<UContentBrowserDataMenuContext_FolderMenu>())
	{
		if (Context->SelectedItems.Num() == 1 && Context->SelectedItems[0].IsFolder())
		{
			return Context;
		}
	}

	return nullptr;
}

#undef LOCTEXT_NAMESPACE
