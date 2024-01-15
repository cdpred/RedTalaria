// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedHermesLevelActorEndpoint : ModuleRules
{
	public RedHermesLevelActorEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		ShortName = "RedHermesLAE";
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
				"ApplicationCore",
				"CoreUObject",
				"EditorSubsystem",
				"Engine",
				"LevelEditor",
				"MainFrame",
				"RedTalariaUrls",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"UnrealEd",
			}
		);
	}
}
