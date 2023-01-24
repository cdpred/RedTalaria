// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "CoreMinimal.h"

class UEdGraph;
class UEdGraphNode;
class UObject;

class FRedHermesGraphNodeEndpointUtils
{
public:
	static UObject* GetGraphOwnerAsset(const UEdGraph* Graph);

	static FString GetFocusUrlForNodeInGraph(const UEdGraphNode* Node, const UEdGraph* Graph);
	static FString GetOpenJumpTargetUrlForNodeInGraph(const UEdGraphNode* Node, const UEdGraph* Graph);
};
