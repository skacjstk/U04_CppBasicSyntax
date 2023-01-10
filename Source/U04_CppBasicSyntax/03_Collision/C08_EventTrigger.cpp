// Fill out your copyright notice in the Description page of Project Settings.


#include "C08_EventTrigger.h"
#include "Global.h"

void AC08_EventTrigger::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AC08_EventTrigger::ActorBeginOverlap);
}

void AC08_EventTrigger::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnDelegate.IsBound())
		OnDelegate.Broadcast(UKismetMathLibrary::RandomIntegerInRange(0,2));
	
}
