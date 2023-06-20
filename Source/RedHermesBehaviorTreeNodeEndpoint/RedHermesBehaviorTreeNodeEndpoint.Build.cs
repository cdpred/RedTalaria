// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedHermesBehaviorTreeNodeEndpoint : ModuleRules
{
	public RedHermesBehaviorTreeNodeEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"AIModule",
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
				"AIGraph",
				"BehaviorTreeEditor",
				"EditorFramework",
			}
		);
	}
}
