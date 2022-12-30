// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

#include "RedTalariaLevelAtCameraCoordsUrls.h"

#include "HermesServer.h"
#include "Algo/Transform.h"

const FName FRedTalariaLevelAtCameraCoordsUrls::HermesEndpointId = TEXT("level_coords");
const FString FRedTalariaLevelAtCameraCoordsUrls::CameraLocationXParamName = TEXT("lx");
const FString FRedTalariaLevelAtCameraCoordsUrls::CameraLocationYParamName = TEXT("ly");
const FString FRedTalariaLevelAtCameraCoordsUrls::CameraLocationZParamName = TEXT("lz");
const FString FRedTalariaLevelAtCameraCoordsUrls::CameraRotationPParamName = TEXT("rp");
const FString FRedTalariaLevelAtCameraCoordsUrls::CameraRotationYParamName = TEXT("ry");
const FString FRedTalariaLevelAtCameraCoordsUrls::CameraRotationRParamName = TEXT("rr");

FString FRedTalariaLevelAtCameraCoordsUrls::GetUrlForLevelAtLocationAtRotation(FName Package, const FVector& Location, const FRotator& Rotation)
{
	if (const auto Hermes = FModuleManager::LoadModulePtr<IHermesServerModule>(TEXT("HermesServer")))
	{
		const TMap<FString, double> QueryParamMap = {
			{CameraLocationXParamName, Location.X},
			{CameraLocationYParamName, Location.Y},
			{CameraLocationZParamName, Location.Z},
			{CameraRotationPParamName, Rotation.Pitch},
			{CameraRotationYParamName, Rotation.Yaw},
			{CameraRotationRParamName, Rotation.Roll}
		};

		TArray<FString> QueryParams;
		Algo::Transform(QueryParamMap, QueryParams, [](const auto& Pair) {
			return FString::Printf(TEXT("%s=%f"), *Pair.Key, Pair.Value);
		});

		return FString::Printf(TEXT("%s?%s"), *Hermes->GetUri(HermesEndpointId, *Package.ToString()), *FString::Join(QueryParams, TEXT("&")));
	}

	return FString(TEXT(""));
}
