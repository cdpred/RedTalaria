// Copyright (c) CD PROJEKT S.A. All Rights Reserved.

using UnrealBuildTool;

public class RedTalaria : ModuleRules
{
	public RedTalaria(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"HermesServer"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"EditorSubsystem",
				"Projects"
			}
		);
	}
}
