// Copyright (c) CD PROJEKT S.A.

#include "RedTalariaLevelActorUrls.h"

#include "HermesServer.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Modules/ModuleManager.h"

const FName FRedTalariaLevelActorUrls::HermesEndpointId = TEXT("level_actor");
const FString FRedTalariaLevelActorUrls::ActorNameParamName = TEXT("actor_name");

FString FRedTalariaLevelActorUrls::GetUrlForLevelActor(FName Package, const FString& ActorName)
{
	if (const auto Hermes = FModuleManager::LoadModulePtr<IHermesServerModule>(TEXT("HermesServer")))
	{
		return FString::Printf(TEXT("%s?%s=%s"), *Hermes->GetUri(HermesEndpointId, *Package.ToString()), *ActorNameParamName, *FGenericPlatformHttp::UrlEncode(ActorName));
	}

	return FString(TEXT(""));
}
