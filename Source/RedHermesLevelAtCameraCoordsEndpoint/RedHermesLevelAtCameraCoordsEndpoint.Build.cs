// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedHermesLevelAtCameraCoordsEndpoint : ModuleRules
{
	public RedHermesLevelAtCameraCoordsEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		ShortName = "RedHermesLACCE";
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
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"RedTalariaUrls",
				"UnrealEd",
				"EditorSubsystem",
				"ToolMenus",
				"LevelEditor",
				"ApplicationCore",
				"MainFrame",
			}
		);
	}
}
