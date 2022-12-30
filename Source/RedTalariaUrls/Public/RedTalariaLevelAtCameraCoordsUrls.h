// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class REDTALARIAURLS_API FRedTalariaLevelAtCameraCoordsUrls
{
public:
	static const FName HermesEndpointId;

	static const FString CameraLocationXParamName;
	static const FString CameraLocationYParamName;
	static const FString CameraLocationZParamName;
	static const FString CameraRotationPParamName;
	static const FString CameraRotationYParamName;
	static const FString CameraRotationRParamName;

	static FString GetUrlForLevelAtLocationAtRotation(FName Package, const FVector& Location, const FRotator& Rotation);
};
