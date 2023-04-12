// Copyright (c) CD PROJEKT S.A.

#include "RedHermesBlueprintNodeEndpoint.h"

#include "EdGraph/EdGraph.h"
#include "EdGraphNode_Comment.h"
#include "Editor.h"
#include "K2Node.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "RedHermesGraphNodeEndpoint.h"
#include "RedHermesGraphNodeEndpointEditorExtension.h"

#define LOCTEXT_NAMESPACE "FRedHermesBlueprintNodeEndpointModule"

void FRedHermesBlueprintNodeEndpointModule::StartupModule()
{
	if (const auto RedHermesGraphNodeEndpoint = GEditor->GetEditorSubsystem<URedHermesGraphNodeEndpoint>())
	{
		OnRequestDelegateHandle = RedHermesGraphNodeEndpoint->OnRequest().AddStatic(&FRedHermesBlueprintNodeEndpointModule::HandleRequest);
	}

	if (const auto NodeExtensionSubsystem = GEditor->GetEditorSubsystem<URedHermesGraphNodeEndpointEditorExtension>())
	{
		OnNodeMenuExtensionHookRequestDelegateHandle = NodeExtensionSubsystem->OnNodeMenuExtensionHookRequest().AddStatic(&FRedHermesBlueprintNodeEndpointModule::ProvideNodeExtensionHook);
	}
}

void FRedHermesBlueprintNodeEndpointModule::ShutdownModule()
{
	if (OnRequestDelegateHandle.IsValid())
	{
		if (GEditor != nullptr)
		{
			if (const auto RedHermesGraphNodeEndpoint = GEditor->GetEditorSubsystem<URedHermesGraphNodeEndpoint>())
			{
				RedHermesGraphNodeEndpoint->OnRequest().Remove(OnRequestDelegateHandle);
			}
			OnRequestDelegateHandle.Reset();
		}
	}

	if (OnNodeMenuExtensionHookRequestDelegateHandle.IsValid())
	{
		if (GEditor != nullptr)
		{
			if (const auto NodeExtensionSubsystem = GEditor->GetEditorSubsystem<URedHermesGraphNodeEndpointEditorExtension>())
			{
				NodeExtensionSubsystem->OnNodeMenuExtensionHookRequest().Remove(OnNodeMenuExtensionHookRequestDelegateHandle);
			}
			OnNodeMenuExtensionHookRequestDelegateHandle.Reset();
		}
	}
}

const UEdGraphNode* FRedHermesBlueprintNodeEndpointModule::GetNodeInAsset(FGuid NodeGuid, const UObject* Asset)
{
	if (const auto BlueprintObj = Cast<UBlueprint>(Asset))
	{
		TArray<UEdGraph*> Graphs;
		BlueprintObj->GetAllGraphs(Graphs);

		for (const UEdGraph* Graph : Graphs)
		{
			for (const UEdGraphNode* Node : Graph->Nodes)
			{
				if (Node->NodeGuid == NodeGuid)
				{
					return Node;
				}
			}
		}
	}

	return nullptr;
}

void FRedHermesBlueprintNodeEndpointModule::HandleRequest(FGuid NodeGuid, UObject* Asset, bool bOpenJumpTarget)
{
	if (const UEdGraphNode* Node = GetNodeInAsset(NodeGuid, Asset))
	{
		const UObject* JumpTarget = Node->GetJumpTargetForDoubleClick();
		FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(bOpenJumpTarget && JumpTarget ? JumpTarget : Node, false);
	}
}

void FRedHermesBlueprintNodeEndpointModule::ProvideNodeExtensionHook(const UEdGraphNode* Node, const UEdGraph* /*Graph*/, TSet<FName>& ExtensionHooks)
{
	if (Node->IsA<UK2Node>() || Node->IsA<UEdGraphNode_Comment>())
	{
		ExtensionHooks.Emplace(FName(TEXT("EdGraphSchemaNodeActions")));
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRedHermesBlueprintNodeEndpointModule, RedHermesBlueprintNodeEndpoint)
