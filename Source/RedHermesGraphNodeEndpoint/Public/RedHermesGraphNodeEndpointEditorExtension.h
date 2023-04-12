// Copyright (c) CD PROJEKT S.A.

#pragma once

#include "EditorSubsystem.h"

#include "RedHermesGraphNodeEndpointEditorExtension.generated.h"

class FMenuBuilder;
class FExtender;
class FUICommandList;
class UEdGraph;
class UEdGraphNode;
class UEdGraphPin;

UCLASS()
class REDHERMESGRAPHNODEENDPOINT_API URedHermesGraphNodeEndpointEditorExtension : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnNodeMenuExtensionHookRequestDelegate, const UEdGraphNode*, const UEdGraph*, TSet<FName>&)

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	FOnNodeMenuExtensionHookRequestDelegate& OnNodeMenuExtensionHookRequest() { return OnNodeMenuExtensionHookRequestDelegate; }

private:
	FOnNodeMenuExtensionHookRequestDelegate OnNodeMenuExtensionHookRequestDelegate;

	TSharedRef<FExtender> HandleOnExtendGraphEditorContextMenu(
		const TSharedRef<FUICommandList> CommandList,
		const UEdGraph* Graph,
		const UEdGraphNode* Node,
		const UEdGraphPin* Pin,
		bool bIsConst);

	struct FCopyUrlMenuEntry
	{
		FText Label;
		FText Tooltip;
		FString UrlToCopy;
	};

	static void HandleOnExtendContextMenu(FMenuBuilder& MenuBuilder, TArray<FCopyUrlMenuEntry> MenuEntries);
};
