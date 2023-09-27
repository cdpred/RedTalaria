// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedHermesAutomationEndpoint : ModuleRules
{
	public RedHermesAutomationEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"RedTalaria",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"AutomationController",
				"CoreUObject",
				"Engine",
				"HTTP",
				"RedTalariaUrls",
				"SessionFrontend",
				"Slate",
				"SlateCore",
				"UnrealEd",
			}
		);
	}
}
