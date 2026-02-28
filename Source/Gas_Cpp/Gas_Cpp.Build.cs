// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Gas_Cpp : ModuleRules
{
	public Gas_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"GameplayAbilities",
			"GameplayTasks",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Gas_Cpp",
			"Gas_Cpp/Variant_Platforming",
			"Gas_Cpp/Variant_Platforming/Animation",
			"Gas_Cpp/Variant_Combat",
			"Gas_Cpp/Variant_Combat/AI",
			"Gas_Cpp/Variant_Combat/Animation",
			"Gas_Cpp/Variant_Combat/Gameplay",
			"Gas_Cpp/Variant_Combat/Interfaces",
			"Gas_Cpp/Variant_Combat/UI",
			"Gas_Cpp/Variant_SideScrolling",
			"Gas_Cpp/Variant_SideScrolling/AI",
			"Gas_Cpp/Variant_SideScrolling/Gameplay",
			"Gas_Cpp/Variant_SideScrolling/Interfaces",
			"Gas_Cpp/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
