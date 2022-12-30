// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedTalariaGraphNodeUrls.h"

#include "HermesServer.h"
#include "Modules/ModuleManager.h"

const FName FRedTalariaGraphNodeUrls::HermesEndpointId = TEXT("graph_node");
const FString FRedTalariaGraphNodeUrls::GuidQueryParamName = TEXT("guid");
const FString FRedTalariaGraphNodeUrls::OpenJumpTargetQueryParamName = TEXT("open_jump_target");

FString FRedTalariaGraphNodeUrls::GetFocusUrlForNode(FName Package, FGuid NodeGuid)
{
	if (const auto Hermes = FModuleManager::LoadModulePtr<IHermesServerModule>(TEXT("HermesServer")))
	{
		return FString::Printf(TEXT("%s?%s=%s"),
			*Hermes->GetUri(HermesEndpointId, *Package.ToString()),
			*GuidQueryParamName,
			*NodeGuid.ToString());
	}

	return FString(TEXT(""));
}

FString FRedTalariaGraphNodeUrls::GetOpenJumpTargetUrlForNode(FName Package, FGuid NodeGuid)
{
	const FString NodeUrl = GetFocusUrlForNode(Package, NodeGuid);
	if (!NodeUrl.IsEmpty())
	{
		return FString::Printf(TEXT("%s&%s"), *NodeUrl, *OpenJumpTargetQueryParamName);
	}

	return FString(TEXT(""));
}
