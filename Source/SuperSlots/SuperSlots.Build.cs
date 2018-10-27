// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SuperSlots : ModuleRules
{
	public SuperSlots(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "SuperSlotsSupport" });
        
        //PublicAdditionalLibraries.Add(@"C:\Unreal_Projects\SuperSlots\Binaries\Win64\SUPERSLOTS-SUPPORT.lib");
        //PublicAdditionalLibraries.Add(ModuleDirectory + @"\..\..\ThirdParty\SuperSlotsSupport\Win64\SUPERSLOTS-SUPPORT_D.lib");
        //PublicSystemIncludePaths.Add(ModuleDirectory + @"\..\..\ThirdParty\SuperSlotsSupport\include");

        //PublicDefinitions.Add("SuperSlotsSupport_LOADDLL");
	}
}
