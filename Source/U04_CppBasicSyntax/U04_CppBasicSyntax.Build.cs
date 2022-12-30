// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U04_CppBasicSyntax : ModuleRules
{
	public U04_CppBasicSyntax(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PublicIncludePaths.Add(ModuleDirectory);	// 추가 포함 디렉토리"./;"

	}
}
