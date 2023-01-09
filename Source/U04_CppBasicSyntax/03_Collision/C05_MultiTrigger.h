// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Collision/C00_BoxBase.h"
#include "C05_MultiTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiBeginOverlap, int32, FLinearColor); // void __ (Int32, LinearColor)
UCLASS()
class U04_CPPBASICSYNTAX_API AC05_MultiTrigger : public AC00_BoxBase
{
	GENERATED_BODY()
public:
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:
	FMultiBeginOverlap OnMultiBeginOverlap;
	
};
