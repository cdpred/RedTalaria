// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedHermesGraphNodeEndpointUtils.h"

#include "RedTalariaGraphNodeUrls.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/IAssetRegistry.h"

UObject* FRedHermesGraphNodeEndpointUtils::GetGraphOwnerAsset(const UEdGraph* Graph)
{
	if (!IsValid(Graph))
	{
		return nullptr;
	}

	// Basically, one of the outer parts of the graph is an asset.
	UObject* TestOuter = Graph->GetOuter();
	while (IsValid(TestOuter))
	{
		if (TestOuter->IsAsset())
		{
			return TestOuter;
		}

		TestOuter = TestOuter->GetOuter();
	}

	// If it is not referencing an asset from the graph,
	// search for the asset with the same name as the outermost object.
	const UObject* OutermostObject = nullptr;
	TestOuter = Graph->GetOuter();
	while (IsValid(TestOuter))
	{
		const UObject* OuterObject = TestOuter->GetOuter();
		const UPackage* TransientPackage = GetTransientPackage();
		if (IsValid(OuterObject) && IsValid(TransientPackage))
		{
			if (OuterObject->GetFullName().Equals(TransientPackage->GetFullName()))
			{
				OutermostObject = TestOuter;
			}
		}

		TestOuter = TestOuter->GetOuter();
	}

	if (!IsValid(OutermostObject))
	{
		return nullptr;
	}

	UObject* SameNameAsset = nullptr;
	const IAssetRegistry& AssetRegistry = FAssetRegistryModule::GetRegistry();
	AssetRegistry.EnumerateAllAssets(
		[&](const FAssetData& AssetData) -> bool {
			if (AssetData.AssetName == OutermostObject->GetFName())
			{
				SameNameAsset = AssetData.GetAsset();
				return false;
			}

			return true;
		});

	return SameNameAsset;
}

FString FRedHermesGraphNodeEndpointUtils::GetFocusUrlForNodeInGraph(const UEdGraphNode* Node, const UEdGraph* Graph)
{
	if (IsValid(Node) && IsValid(Graph))
	{
		if (const UObject* Asset = GetGraphOwnerAsset(Graph))
		{
			return FRedTalariaGraphNodeUrls::GetFocusUrlForNode(Asset->GetOutermost()->GetFName(), Node->NodeGuid);
		}
	}

	return FString();
}

FString FRedHermesGraphNodeEndpointUtils::GetOpenJumpTargetUrlForNodeInGraph(const UEdGraphNode* Node, const UEdGraph* Graph)
{
	if (IsValid(Node) && IsValid(Graph))
	{
		if (Node->GetJumpTargetForDoubleClick() != nullptr)
		{
			if (const UObject* Asset = GetGraphOwnerAsset(Graph))
			{
				return FRedTalariaGraphNodeUrls::GetOpenJumpTargetUrlForNode(Asset->GetOutermost()->GetFName(), Node->NodeGuid);
			}
		}
	}

	return FString();
}
