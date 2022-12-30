// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedHermesEndpoint.h"

#include "RedHermesLevelAtCameraCoordsEndpoint.generated.h"

UCLASS()
class URedHermesLevelAtCameraCoordsEndpoint : public URedHermesEndpoint
{
	GENERATED_BODY()

protected:
	virtual FName GetHermesEndpointId() const override;
	virtual void ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const override;
};
