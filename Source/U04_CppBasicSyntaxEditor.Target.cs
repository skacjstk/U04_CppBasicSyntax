// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class U04_CppBasicSyntaxEditorTarget : TargetRules
{
	public U04_CppBasicSyntaxEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "U04_CppBasicSyntax" } );
	}
}
