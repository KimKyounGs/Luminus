// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LuminusGame : ModuleRules
{
	public LuminusGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"});
	}
}
