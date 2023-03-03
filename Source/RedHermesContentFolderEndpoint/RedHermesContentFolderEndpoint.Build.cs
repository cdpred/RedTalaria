// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedHermesContentFolderEndpoint : ModuleRules
{
	public RedHermesContentFolderEndpoint(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// TMP
		PCHUsage = PCHUsageMode.NoPCHs;
		bUseUnity = false;
		bEnforceIWYU = true;

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
				"RedTalaria",
				"RedTalariaUrls",
				"EditorSubsystem",
				"ContentBrowserData",
				"ToolMenus",
				"ApplicationCore"
			}
		);
	}
}
