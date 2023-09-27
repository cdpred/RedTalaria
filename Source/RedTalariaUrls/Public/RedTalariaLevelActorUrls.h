// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Containers/UnrealString.h"
#include "UObject/NameTypes.h"

class REDTALARIAURLS_API FRedTalariaLevelActorUrls
{
public:
	static const FName HermesEndpointId;
	static const FString ActorNameParamName;

	static FString GetUrlForLevelActor(FName Package, const FString& ActorName);
};
