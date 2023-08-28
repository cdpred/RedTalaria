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
			}
		);

		BuildVersion Version;
		if (BuildVersion.TryRead(BuildVersion.GetDefaultFileName(), out Version))
		{
			if (Version.MajorVersion >= 5)
			{
				PrivateDependencyModuleNames.Add("EditorFramework");
			}
		}
	}
}
