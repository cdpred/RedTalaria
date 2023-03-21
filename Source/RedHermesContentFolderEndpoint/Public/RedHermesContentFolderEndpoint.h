// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "RedHermesEndpoint.h"

#include "RedHermesContentFolderEndpoint.generated.h"

UCLASS()
class REDHERMESCONTENTFOLDERENDPOINT_API URedHermesContentFolderEndpoint : public URedHermesEndpoint
{
	GENERATED_BODY()

protected:
	virtual FName GetHermesEndpointId() const override;
	virtual void ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const override;
};
