// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "HAL/Platform.h"
#include "UObject/NameTypes.h"

class REDTALARIAURLS_API FRedTalariaContentFolderUrls
{
public:
	static const FName HermesEndpointId;

	static FString GetUrlForContentFolder(FName FolderPath);
};
