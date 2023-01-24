// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleInterface.h"
#include "UObject/NameTypes.h"

class UObject;
class UEdGraphNode;
class UEdGraph;

class FRedHermesBlueprintNodeEndpointModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FDelegateHandle OnRequestDelegateHandle;
	FDelegateHandle OnNodeMenuExtensionHookRequestDelegateHandle;

	static const UEdGraphNode* GetNodeInAsset(FGuid NodeGuid, const UObject* Asset);
	static void HandleRequest(FGuid NodeGuid, UObject* Asset, bool bOpenJumpTarget);
	static void ProvideNodeExtensionHook(const UEdGraphNode* Node, const UEdGraph* Graph, TSet<FName>& ExtensionHooks);
};
