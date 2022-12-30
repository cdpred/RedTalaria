// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

using UnrealBuildTool;

public class RedHermesBlueprintNodeEndpoint : ModuleRules
{
	public RedHermesBlueprintNodeEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"RedHermesGraphNodeEndpoint",
				"BlueprintGraph"
			}
		);
	}
}
