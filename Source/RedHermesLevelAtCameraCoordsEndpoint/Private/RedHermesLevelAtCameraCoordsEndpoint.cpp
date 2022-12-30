// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedHermesLevelAtCameraCoordsEndpoint.h"

#include "Editor.h"
#include "LevelEditorViewport.h"
#include "RedTalariaLevelAtCameraCoordsUrls.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Interfaces/IMainFrameModule.h"
#include "Subsystems/AssetEditorSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogRedHermesLevelAtCameraCoordsEndpoint, Log, All);

FName URedHermesLevelAtCameraCoordsEndpoint::GetHermesEndpointId() const
{
	return FRedTalariaLevelAtCameraCoordsUrls::HermesEndpointId;
}

void URedHermesLevelAtCameraCoordsEndpoint::ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const
{
	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry")).Get();
	TArray<FAssetData> AssetData;
	AssetRegistry.GetAssetsByPackageName(*Path, AssetData);

	if (AssetData.Num() > 0)
	{
		UObject* Asset = AssetData[0].GetAsset();
		if (Asset->IsA<UWorld>())
		{
			UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
			AssetEditorSubsystem->OpenEditorForAsset(Asset);

			if (
				QueryParams.Contains(FRedTalariaLevelAtCameraCoordsUrls::CameraLocationXParamName) &&
				QueryParams.Contains(FRedTalariaLevelAtCameraCoordsUrls::CameraLocationYParamName) &&
				QueryParams.Contains(FRedTalariaLevelAtCameraCoordsUrls::CameraLocationZParamName) &&
				QueryParams.Contains(FRedTalariaLevelAtCameraCoordsUrls::CameraRotationPParamName) &&
				QueryParams.Contains(FRedTalariaLevelAtCameraCoordsUrls::CameraRotationYParamName) &&
				QueryParams.Contains(FRedTalariaLevelAtCameraCoordsUrls::CameraRotationRParamName)
			)
			{
				for (FLevelEditorViewportClient* LevelVC : GEditor->GetLevelViewportClients())
				{
					if (LevelVC && LevelVC->IsPerspective())
					{
						LevelVC->SetViewLocation({
							FCString::Atof(*QueryParams[FRedTalariaLevelAtCameraCoordsUrls::CameraLocationXParamName]),
							FCString::Atof(*QueryParams[FRedTalariaLevelAtCameraCoordsUrls::CameraLocationYParamName]),
							FCString::Atof(*QueryParams[FRedTalariaLevelAtCameraCoordsUrls::CameraLocationZParamName])
						});
						LevelVC->SetViewRotation({
							FCString::Atof(*QueryParams[FRedTalariaLevelAtCameraCoordsUrls::CameraRotationPParamName]),
							FCString::Atof(*QueryParams[FRedTalariaLevelAtCameraCoordsUrls::CameraRotationYParamName]),
							FCString::Atof(*QueryParams[FRedTalariaLevelAtCameraCoordsUrls::CameraRotationRParamName])
						});
						break;
					}
				}
			}

			const IMainFrameModule& MainFrameModule = IMainFrameModule::Get();
			const TSharedPtr<SWindow> ParentWindow = MainFrameModule.GetParentWindow();

			if (ParentWindow.IsValid())
			{
				ParentWindow->ShowWindow();
				ParentWindow->GetNativeWindow()->HACK_ForceToFront();
			}
		}
		else
		{
			UE_LOG(LogRedHermesLevelAtCameraCoordsEndpoint, Error, TEXT("Asset for path %s is not a UWorld."), *Path);
		}
	}
	else
	{
		UE_LOG(LogRedHermesLevelAtCameraCoordsEndpoint, Error, TEXT("Failed loading asset for path %s."), *Path);
	}
}
