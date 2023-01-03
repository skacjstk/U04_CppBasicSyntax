#pragma once

#include "CoreMinimal.h"

#define PrintLine() { CLog::Log(__FUNCTION__, __LINE__);}

class U04_CPPBASICSYNTAX_API CLog
{
public:
	static void Print(const FString& InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);	// 테스트
	static void Print(int32 InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float InDuration = 5.0f, FColor InColor = FColor::Blue);

	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InObject);
	static void Log(const FString& InFuncName, int32 InLineNumber);	// 여기까지 들어오는지 검사
};
