// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "UObject/NameTypes.h"

class REDTALARIAURLS_API FRedTalariaContentUrls
{
public:
	static const FName HermesEndpointId;

	static FString GetUrlForPackage(FName PackageName);
};
