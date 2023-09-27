// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "Runtime/Launch/Resources/Version.h"

#include "RedHermesEndpoint.h"

#include "RedHermesLevelActorEndpoint.generated.h"

class UWorldPartition;
class FLoaderAdapterActorList;

UCLASS()
class URedHermesLevelActorEndpoint : public URedHermesEndpoint
{
	GENERATED_BODY()

protected:
	virtual FName GetHermesEndpointId() const override;
	virtual void ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const override;

private:
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	static TMap<UWorldPartition*, TUniquePtr<FLoaderAdapterActorList>> LoaderAdapterActorListMap;
	static FDelegateHandle OnWorldPartitionUninitializedHandle;

	static void OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition);
	static void LoadActor(UWorldPartition* WorldPartition, FGuid ActorGuid);
#endif
};
