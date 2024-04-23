// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedHermesGraphNodeEndpoint : ModuleRules
{
	public RedHermesGraphNodeEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		ShortName = "RedHermesGNE";
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
				"AssetRegistry",
				"CoreUObject",
				"Engine",
				"RedTalariaUrls",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"UnrealEd",
				"EditorSubsystem",
				"MainFrame",
			}
		);
	}
}
