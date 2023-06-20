// Copyright (c) CD PROJEKT S.A.

#pragma once

// The engine commit that is needed for this to work: https://github.com/EpicGames/UnrealEngine/commit/6bb52ead8294554e5bdb60f637729eae397942d8 .

#include "Modules/ModuleInterface.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
#include "Delegates/IDelegateInstance.h"
#include "UObject/NameTypes.h"

class UObject;
class UEdGraphNode;
class UEdGraph;
#endif

class FRedHermesBehaviorTreeNodeEndpointModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	FDelegateHandle OnRequestDelegateHandle;
	FDelegateHandle OnNodeMenuExtensionHookRequestDelegateHandle;

	static UEdGraphNode* GetNodeInAsset(FGuid NodeGuid, const UObject* Asset);
	static void HandleRequest(FGuid NodeGuid, UObject* Asset, bool bOpenJumpTarget);
	static void ProvideNodeExtensionHook(const UEdGraphNode* Node, const UEdGraph* Graph, TSet<FName>& ExtensionHooks);
#endif
};
