// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#pragma once

#include "RedHermesEndpoint.h"

#include "IAutomationControllerManager.h"

#include "RedHermesAutomationEndpoint.generated.h"

UCLASS()
class REDHERMESAUTOMATIONENDPOINT_API URedHermesAutomationEndpoint : public URedHermesEndpoint
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

protected:
	virtual FName GetHermesEndpointId() const override;
	virtual void ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const override;

private:
	IAutomationControllerManagerPtr AutomationController;
	FDelegateHandle TestAvailableHandle;

	void RunTestsWithNameFilter(FString TestNameFilter) const;
};
