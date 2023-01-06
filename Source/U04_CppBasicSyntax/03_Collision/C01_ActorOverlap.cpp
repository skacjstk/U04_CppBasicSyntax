// Fill out your copyright notice in the Description page of Project Settings.


#include "C01_ActorOverlap.h"
#include "Global.h"

void AC01_ActorOverlap::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AC01_ActorOverlap::ActorBeginOverlap);
}

void AC01_ActorOverlap::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	CLog::Print(OtherActor->GetName() + " is Coming.");
}

