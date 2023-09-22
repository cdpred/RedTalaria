// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "EditorSubsystem.h"
#include "HermesServer.h"

#include "RedHermesEndpoint.generated.h"

UCLASS(Abstract)
class REDTALARIA_API URedHermesEndpoint : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

protected:
	virtual FName GetHermesEndpointId() const
		PURE_VIRTUAL(URedHermesEndpoint::GetHermesEndpointId, return NAME_None;);

	virtual void ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const
		PURE_VIRTUAL(URedHermesEndpoint::ProcessRequest,);

private:
	struct FPendingRequest
	{
		FString Path;
		FHermesQueryParamsMap Query;
	};

	TArray<FPendingRequest> PendingRequests;

	void OnAssetRegistryFilesLoaded();
	void OnHermesRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams);
};
