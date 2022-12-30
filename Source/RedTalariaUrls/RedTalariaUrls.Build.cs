// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

using UnrealBuildTool;

public class RedTalariaUrls : ModuleRules
{
	public RedTalariaUrls(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
		);

		PrivateIncludePathModuleNames.AddRange(
			new[]
			{
				"HermesServer",
			}
		);
	}
}
