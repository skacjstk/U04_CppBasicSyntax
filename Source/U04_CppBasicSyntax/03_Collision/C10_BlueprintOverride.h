// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Collision/C00_BoxBase.h"
#include "C10_BlueprintOverride.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API AC10_BlueprintOverride : public AC00_BoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
private:
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:
	UFUNCTION(BlueprintImplementableEvent)
		void SetBodyColor();
};
