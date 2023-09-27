// Copyright (c) CD PROJEKT S.A.

#include "RedHermesLevelActorEndpoint.h"

#include "Editor.h"
#include "RedTalariaLevelActorUrls.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Subsystems/AssetEditorSubsystem.h"

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
#include "WorldPartition/WorldPartition.h"
#include "WorldPartition/WorldPartitionHelpers.h"
#include "WorldPartition/LoaderAdapter/LoaderAdapterActorList.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogRedHermesLevelActorEndpoint, Log, All);

#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
TMap<UWorldPartition*, TUniquePtr<FLoaderAdapterActorList>> URedHermesLevelActorEndpoint::LoaderAdapterActorListMap;
FDelegateHandle URedHermesLevelActorEndpoint::OnWorldPartitionUninitializedHandle;

void URedHermesLevelActorEndpoint::OnWorldPartitionUninitialized(UWorldPartition* InWorldPartition)
{
	if (auto* LoaderAdapterActorList = LoaderAdapterActorListMap.Find(InWorldPartition))
	{
		LoaderAdapterActorList->Get()->Unload();
	}

	LoaderAdapterActorListMap.Remove(InWorldPartition);
	if (LoaderAdapterActorListMap.IsEmpty())
	{
		InWorldPartition->GetWorld()->OnWorldPartitionUninitialized().Remove(OnWorldPartitionUninitializedHandle);
	}
}

void URedHermesLevelActorEndpoint::LoadActor(UWorldPartition* WorldPartition, FGuid ActorGuid)
{
	if (WorldPartition == nullptr)
	{
		return;
	}

	if (LoaderAdapterActorListMap.IsEmpty())
	{
		OnWorldPartitionUninitializedHandle = WorldPartition->GetWorld()->OnWorldPartitionUninitialized().AddStatic(&ThisClass::OnWorldPartitionUninitialized);
	}

	TUniquePtr<FLoaderAdapterActorList>& LoaderAdapterActorList = LoaderAdapterActorListMap.FindOrAdd(WorldPartition, MakeUnique<FLoaderAdapterActorList>(WorldPartition->GetWorld()));
	LoaderAdapterActorList->AddActors({ActorGuid});
}
#endif

FName URedHermesLevelActorEndpoint::GetHermesEndpointId() const
{
	return FRedTalariaLevelActorUrls::HermesEndpointId;
}

void URedHermesLevelActorEndpoint::ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const
{
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	TArray<FAssetData> AssetData;
	AssetRegistry.GetAssetsByPackageName(*Path, AssetData);

	if (AssetData.IsEmpty())
	{
		UE_LOG(LogRedHermesLevelActorEndpoint, Error, TEXT("Failed loading asset for path %s."), *Path);
		return;
	}

	const auto* Actor = Cast<AActor>(AssetData[0].GetAsset());
	if (Actor == nullptr)
	{
		UE_LOG(LogRedHermesLevelActorEndpoint, Error, TEXT("Asset for path %s is not an AActor."), *Path);
		return;
	}

	const UWorld* ActorWorld = Actor->GetWorld();
	if (ActorWorld == nullptr)
	{
		UE_LOG(LogRedHermesLevelActorEndpoint, Error, TEXT("World for actor %s is null."), *Actor->GetActorNameOrLabel());
		return;
	}

	if (GEditor->GetEditorWorldContext().World() != ActorWorld)
	{
		if (auto* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>())
		{
			AssetEditorSubsystem->OpenEditorForAsset(ActorWorld);
		}
	}

	GEditor->GetTimerManager()->SetTimerForNextTick(FTimerDelegate::CreateLambda(
		[Path]() {
			TArray<FAssetData> AssetData;
			const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
			AssetRegistry.GetAssetsByPackageName(*Path, AssetData);

			if (auto* ActorToSelect = Cast<AActor>(AssetData[0].GetAsset()))
			{
				if (const UWorld* World = ActorToSelect->GetWorld())
				{
					if (World->IsPartitionedWorld())
					{
						LoadActor(FWorldPartitionHelpers::GetWorldPartition(ActorToSelect), ActorToSelect->GetActorGuid());
					}
				}

				FGlobalTabmanager::Get()->TryInvokeTab(FTabId(TEXT("LevelEditor")));

				GEditor->SelectNone(true, true);
				GEditor->SelectActor(ActorToSelect, true, true, true, true);
				GEditor->MoveViewportCamerasToActor(*ActorToSelect, false);
			}
		}));

	const IMainFrameModule& MainFrameModule = IMainFrameModule::Get();
	const TSharedPtr<SWindow> ParentWindow = MainFrameModule.GetParentWindow();

	if (ParentWindow.IsValid())
	{
		ParentWindow->ShowWindow();
		ParentWindow->GetNativeWindow()->HACK_ForceToFront();
	}
#endif
}
