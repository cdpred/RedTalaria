// Copyright (c) CD PROJEKT S.A.

using UnrealBuildTool;

public class RedTalariaUrls : ModuleRules
{
	public RedTalariaUrls(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
				"HTTP",
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
