// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Containers/UnrealString.h"
#include "UObject/NameTypes.h"

class REDTALARIAURLS_API FRedTalariaGraphNodeUrls
{
public:
	static const FName HermesEndpointId;
	static const FString GuidQueryParamName;
	static const FString OpenJumpTargetQueryParamName;

	static FString GetFocusUrlForNode(FName Package, FGuid NodeGuid);
	static FString GetOpenJumpTargetUrlForNode(FName Package, FGuid NodeGuid);
};
