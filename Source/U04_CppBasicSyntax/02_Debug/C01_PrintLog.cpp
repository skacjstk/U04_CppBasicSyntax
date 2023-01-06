// Fill out your copyright notice in the Description page of Project Settings.


#include "C01_PrintLog.h"
#include "Global.h"

// Sets default values
AC01_PrintLog::AC01_PrintLog()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AC01_PrintLog::BeginPlay()
{
	Super::BeginPlay();

//	CLog::Print(1);
//	CLog::Print(2, 1);
//	CLog::Print(3, 2, 20.0f, FColor::Green);	// 같은 
//	CLog::Print(4, 2, 20.0f, FColor::Red);
//	CLog::Print("Hello World");
//	CLog::Print(GetActorLocation());
//	CLog::Print(GetActorRotation());
//
//
//	CLog::Log(10);
//	CLog::Log(PI);
//	CLog::Log("Hell World");
//	CLog::Log(GetActorLocation());
//	CLog::Log(GetActorRotation());
//	CLog::Log(__FILE__);
//	CLog::Log(__FUNCTION__, __LINE__);
//	PrintLine();

}

// Called every frame
void AC01_PrintLog::Tick(float DeltaTime)
{
//	Super::Tick(DeltaTime);
//	RunningTime += DeltaTime;
//	CLog::Print(RunningTime,30);


}

