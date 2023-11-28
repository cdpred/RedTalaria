// Copyright (c) CD PROJEKT S.A.

#include "RedHermesAutomationEndpoint.h"

#include "RedTalariaAutomationUrls.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION >= 5
#include "AutomationGroupFilter.h"
#include "Editor.h"
#include "IAutomationControllerModule.h"
#include "ISessionFrontendModule.h"
#include "TimerManager.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Misc/FilterCollection.h"
#endif

DEFINE_LOG_CATEGORY_STATIC(LogRedHermesAutomationEndpoint, Log, All);

void URedHermesAutomationEndpoint::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
#if ENGINE_MAJOR_VERSION >= 5
	auto* AutomationControllerModule = &FModuleManager::LoadModuleChecked<IAutomationControllerModule>("AutomationController");
	AutomationController = AutomationControllerModule->GetAutomationController();
	AutomationController->Init();
	AutomationController->Startup();
#endif
}

FName URedHermesAutomationEndpoint::GetHermesEndpointId() const
{
	return FRedTalariaAutomationUrls::HermesEndpointId;
}

void URedHermesAutomationEndpoint::ProcessRequest(const FString& Path, const FHermesQueryParamsMap& QueryParams) const
{
#if ENGINE_MAJOR_VERSION >= 5
	if (!QueryParams.Contains(FRedTalariaAutomationUrls::TestNameFilterParamName))
	{
		return;
	}

	auto& SessionFrontend = FModuleManager::LoadModuleChecked<ISessionFrontendModule>("SessionFrontend");
	SessionFrontend.InvokeSessionFrontend(FName("AutomationPanel"));

	FString TestNameFilter = FGenericPlatformHttp::UrlDecode(QueryParams[FRedTalariaAutomationUrls::TestNameFilterParamName]).TrimStartAndEnd();
	FTimerHandle TimerHandle;
	const float Delay = (AutomationController->GetTestState() == EAutomationControllerModuleState::Ready) ? 1.f : 10.f;
	GEditor->GetTimerManager()->SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ThisClass::RunTestsWithNameFilter, MoveTemp(TestNameFilter)), Delay, false);
#endif
}

void URedHermesAutomationEndpoint::RunTestsWithNameFilter(FString TestNameFilter) const
{
#if ENGINE_MAJOR_VERSION >= 5
	if (TestNameFilter.IsEmpty())
	{
		return;
	}

	TArray<FAutomatedTestFilter> FiltersList;
	constexpr bool bMatchFromStart = false;
	constexpr bool bMatchFromEnd = false;

	FiltersList.Add(FAutomatedTestFilter(TestNameFilter, bMatchFromStart, bMatchFromEnd));
	FAutomationGroupFilter* FilterForGivenStr = new FAutomationGroupFilter();
	FilterForGivenStr->SetFilters(FiltersList);
	TSharedPtr<AutomationFilterCollection> AutomationFilters = MakeShareable(new AutomationFilterCollection());
	AutomationFilters->Add(MakeShareable(FilterForGivenStr));

	AutomationController->SetVisibleTestsEnabled(false);
	AutomationController->SetFilter(AutomationFilters);
	AutomationController->SetVisibleTestsEnabled(true);
	TArray<FString> FilteredTestNames;
	AutomationController->GetEnabledTestNames(FilteredTestNames);
	AutomationController->SetEnabledTests(FilteredTestNames);
	AutomationController->OnTestsRefreshed().Broadcast();

	AutomationController->RunTests();
#endif
}
