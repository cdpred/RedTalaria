// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "EditorSubsystem.h"
#include "ToolMenuContext.h"

#include "RedHermesContentFolderEndpointEditorExtension.generated.h"

class UContentBrowserDataMenuContext_FolderMenu;

UCLASS()
class REDHERMESCONTENTFOLDERENDPOINT_API URedHermesContentFolderEndpointEditorExtension : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

private:
	void RegisterContentBrowserFolderContextExtender();
	void UnregisterContentBrowserFolderContextExtender();

	static const UContentBrowserDataMenuContext_FolderMenu* GetContextWithSingleFolderSelected(const FToolMenuContext& MenuContext);
};
