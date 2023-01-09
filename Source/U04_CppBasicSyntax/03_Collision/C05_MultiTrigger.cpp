// Fill out your copyright notice in the Description page of Project Settings.


#include "C05_MultiTrigger.h"
#include "Global.h"

void AC05_MultiTrigger::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AC05_MultiTrigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AC05_MultiTrigger::ActorEndOverlap);
}

void AC05_MultiTrigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnMultiBeginOverlap.IsBound()) 
	{
		int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
		FLinearColor color = FLinearColor::MakeRandomColor();
		OnMultiBeginOverlap.Broadcast(index, color);
	}
}

void AC05_MultiTrigger::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}
