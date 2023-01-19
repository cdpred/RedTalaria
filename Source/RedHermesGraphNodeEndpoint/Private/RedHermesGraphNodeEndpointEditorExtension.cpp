// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedHermesGraphNodeEndpointEditorExtension.h"

#include "Algo/AllOf.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "GraphEditorModule.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Modules/ModuleManager.h"
#include "RedHermesGraphNodeEndpointUtils.h"
#include "RedTalaria.h"

#define LOCTEXT_NAMESPACE "Editor.RedHermesGraphNodeEndpointEditorExtension"

const FName GraphEditorModuleName(TEXT("GraphEditor"));

void URedHermesGraphNodeEndpointEditorExtension::Initialize(FSubsystemCollectionBase& Collection)
{
	auto& GraphEditorModule = FModuleManager::LoadModuleChecked<FGraphEditorModule>(GraphEditorModuleName);
	GraphEditorModule.GetAllGraphEditorContextMenuExtender().Add(
		FGraphEditorModule::FGraphEditorMenuExtender_SelectedNode::CreateUObject(this, &ThisClass::HandleOnExtendGraphEditorContextMenu));
}

void URedHermesGraphNodeEndpointEditorExtension::Deinitialize()
{
	if (const auto GraphEditorModule = FModuleManager::GetModulePtr<FGraphEditorModule>(GraphEditorModuleName))
	{
		GraphEditorModule->GetAllGraphEditorContextMenuExtender().RemoveAll(
			[](const FGraphEditorModule::FGraphEditorMenuExtender_SelectedNode& Delegate) {
				const FName LocalFunction = GET_FUNCTION_NAME_CHECKED(ThisClass, HandleOnExtendGraphEditorContextMenu);
				return Delegate.TryGetBoundFunctionName() == LocalFunction;
			});
	}
}

TSharedRef<FExtender> URedHermesGraphNodeEndpointEditorExtension::HandleOnExtendGraphEditorContextMenu(
	const TSharedRef<FUICommandList> CommandList,
	const UEdGraph* Graph,
	const UEdGraphNode* Node,
	const UEdGraphPin* Pin,
	bool /* bIsConst */)
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();

	TSet<FName> ExtensionHooks;
	OnNodeMenuExtensionHookRequestDelegate.Broadcast(Node, Graph, ExtensionHooks);

	for (const FName ExtensionHook : ExtensionHooks)
	{
		TArray<FCopyUrlMenuEntry> MenuEntries = {
			{LOCTEXT("NodeAction.CopyFocusUrl", "Copy 'Focus node' URL"),
				LOCTEXT("NodeAction.CopyFocusUrlTooltip", "Copy an URL that will open this asset and focus on this node."),
				FRedHermesGraphNodeEndpointUtils::GetFocusUrlForNodeInGraph(Node, Graph)},
			{LOCTEXT("NodeAction.CopyJumpTargetUrl", "Copy 'Open node' URL"),
				LOCTEXT("NodeAction.CopyJumpTargetUrlTooltip", "Copy an URL that will open (the jump target of) this node."),
				FRedHermesGraphNodeEndpointUtils::GetOpenJumpTargetUrlForNodeInGraph(Node, Graph)}};

		Extender->AddMenuExtension(
			ExtensionHook,
			EExtensionHook::Before,
			CommandList,
			FMenuExtensionDelegate::CreateStatic(&ThisClass::HandleOnExtendContextMenu, MoveTemp(MenuEntries)));
	}

	return Extender;
}

void URedHermesGraphNodeEndpointEditorExtension::HandleOnExtendContextMenu(FMenuBuilder& MenuBuilder, TArray<FCopyUrlMenuEntry> MenuEntries)
{
	if (Algo::AllOf(MenuEntries, [](const FCopyUrlMenuEntry& Entry) { return Entry.UrlToCopy.IsEmpty(); }))
	{
		return;
	}

	MenuBuilder.BeginSection(NAME_None, LOCTEXT("SectionName", "Hermes"));
	for (const FCopyUrlMenuEntry& Entry : MenuEntries)
	{
		if (!Entry.UrlToCopy.IsEmpty())
		{
			MenuBuilder.AddMenuEntry(
				Entry.Label,
				Entry.Tooltip,
				FSlateIcon(FRedTalariaModule::SlateStyleSetName, FRedTalariaModule::TalariaIconSlateStyleName),
				FUIAction(FExecuteAction::CreateLambda([UrlToCopy = Entry.UrlToCopy]() {
					FPlatformApplicationMisc::ClipboardCopy(*UrlToCopy);
				})));
		}
	}
	MenuBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE
