// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RedHermesEndpoint.h"

#include "RedHermesGraphNodeEndpoint.generated.h"

UCLASS()
class REDHERMESGRAPHNODEENDPOINT_API URedHermesGraphNodeEndpoint : public URedHermesEndpoint
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnReqestDelegate, FGuid NodeGuid, UObject* Asset, bool bOpenJumpTarget)

	FOnReqestDelegate& OnRequest() { return OnRequestDelegate; }

protected:
	virtual FName GetHermesEndpointId() const override;
	virtual void ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const override;

private:
	FOnReqestDelegate OnRequestDelegate;
};
