// Copyright (c) CD PROJEKT S.A.

#include "RedHermesBehaviorTreeNodeEndpoint.h"

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
#include "BehaviorTreeGraphNode.h"
#include "Editor.h"
#include "IBehaviorTreeEditor.h"
#include "RedHermesGraphNodeEndpoint.h"
#include "RedHermesGraphNodeEndpointEditorExtension.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EdGraph/EdGraph.h"
#include "Toolkits/ToolkitManager.h"
#endif

#define LOCTEXT_NAMESPACE "FRedHermesBehaviorTreeNodeEndpointModule"

void FRedHermesBehaviorTreeNodeEndpointModule::StartupModule()
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	if (const auto RedHermesGraphNodeEndpoint = GEditor->GetEditorSubsystem<URedHermesGraphNodeEndpoint>())
	{
		OnRequestDelegateHandle = RedHermesGraphNodeEndpoint->OnRequest().AddStatic(&FRedHermesBehaviorTreeNodeEndpointModule::HandleRequest);
	}

	if (const auto NodeExtensionSubsystem = GEditor->GetEditorSubsystem<URedHermesGraphNodeEndpointEditorExtension>())
	{
		OnNodeMenuExtensionHookRequestDelegateHandle = NodeExtensionSubsystem->OnNodeMenuExtensionHookRequest().AddStatic(&FRedHermesBehaviorTreeNodeEndpointModule::ProvideNodeExtensionHook);
	}
#endif
}

void FRedHermesBehaviorTreeNodeEndpointModule::ShutdownModule()
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
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
#endif
}

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
UEdGraphNode* FRedHermesBehaviorTreeNodeEndpointModule::GetNodeInAsset(FGuid NodeGuid, const UObject* Asset)
{

	if (const auto BehaviorTreeObj = Cast<UBehaviorTree>(Asset))
	{
		for (UEdGraphNode* Node : BehaviorTreeObj->BTGraph->Nodes)
		{
			if (Node->NodeGuid == NodeGuid)
			{
				return Node;
			}
		}
	}

	return nullptr;
}

void FRedHermesBehaviorTreeNodeEndpointModule::HandleRequest(FGuid NodeGuid, UObject* Asset, bool bOpenJumpTarget)
{
	if (UEdGraphNode* Node = GetNodeInAsset(NodeGuid, Asset))
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Asset);
		TSharedPtr<IToolkit> FoundAssetEditor = FToolkitManager::Get().FindEditorForAsset(Asset);
		if (FoundAssetEditor.IsValid())
		{
			auto BehaviorTreeEditor = StaticCastSharedPtr<IBehaviorTreeEditor>(FoundAssetEditor);
			BehaviorTreeEditor->FocusWindow();
			bOpenJumpTarget ? BehaviorTreeEditor->DoubleClickNode(Node) : BehaviorTreeEditor->FocusAttentionOnNode(Node);
		}
	}
}

void FRedHermesBehaviorTreeNodeEndpointModule::ProvideNodeExtensionHook(const UEdGraphNode* Node, const UEdGraph* /*Graph*/, TSet<FName>& ExtensionHooks)
{
	if (Node->IsA<UBehaviorTreeGraphNode>())
	{
		ExtensionHooks.Emplace(FName(TEXT("BehaviorTreeGraphSchemaNodeActions")));
	}
}
#endif

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FRedHermesBehaviorTreeNodeEndpointModule, RedHermesBehaviorTreeNodeEndpoint)
