// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "EditorSubsystem.h"

#include "RedHermesLevelActorEndpointEditorExtension.generated.h"

class FExtender;
class FUICommandList;
class FMenuBuilder;
class AActor;

UCLASS()
class URedHermesLevelActorEndpointEditorExtension : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void RegisterExtender();
	void UnregisterExtender();

	static TSharedRef<FExtender> HandleOnExtendLevelEditorActorContextMenu(const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> SelectedActors);
	static void HandleOnExtendContextMenu(FMenuBuilder& MenuBuilder, FString UrlsToCopy);
};
