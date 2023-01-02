#pragma once

#include "CoreMinimal.h"

class U04_CPPBASICSYNTAX_API CLog
{
public:
	static void Print(const FString& InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);	// ев
	static void Print(int32 InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
};
