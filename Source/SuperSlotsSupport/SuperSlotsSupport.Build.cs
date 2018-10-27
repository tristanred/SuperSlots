using System;
using System.IO;
using UnrealBuildTool;

public class SuperSlotsSupport : ModuleRules
{
    public SuperSlotsSupport(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;
        
        PublicDefinitions.Add("SuperSlotsSupport_LOADDLL");

        PublicAdditionalLibraries.Add(ModuleDirectory + "/Win64/SUPERSLOTS-SUPPORT_D.lib");
        PublicSystemIncludePaths.Add(ModuleDirectory + @"/include");
        
        CopyToBinaries(ModuleDirectory + "/Win64/SUPERSLOTS-SUPPORT_D.dll", Target);
        CopyToBinaries(ModuleDirectory + "/Win64/SUPERSLOTS-SUPPORT_D.lib", Target);
    }

    private void CopyToBinaries(string Filepath, ReadOnlyTargetRules Target)
    {
        string _TargetFolder = Path.Combine(ModuleDirectory, @"..\..", "Binaries", Target.Platform.ToString());
        string _TargetFile = Path.Combine(_TargetFolder, Path.GetFileName(Filepath));

        File.Copy(Filepath, _TargetFile, true);

        return;
    }
}