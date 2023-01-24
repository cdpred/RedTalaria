// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "CoreMinimal.h"

#include "EditorSubsystem.h"

#include "RedHermesLevelAtCameraCoordsEndpointEditorExtension.generated.h"

UCLASS()
class URedHermesLevelAtCameraCoordsEndpointEditorExtension : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void RegisterViewportOptionMenuExtender();
	void UnregisterViewportOptionMenuExtender();
};
