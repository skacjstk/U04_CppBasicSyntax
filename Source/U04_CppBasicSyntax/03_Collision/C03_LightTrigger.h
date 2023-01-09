// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Collision/C00_BoxBase.h"
#include "C03_LightTrigger.generated.h"

DECLARE_DELEGATE(FBoxBeginOverlap);	// void() 타입 
DECLARE_DELEGATE(FBoxEndOverlap);	// void() 타입 우리가 직접 지정한 이름
DECLARE_DELEGATE_RetVal_OneParam(FString, FBoxBeginRandomLightColor, FLinearColor);


UCLASS()
class U04_CPPBASICSYNTAX_API AC03_LightTrigger : public AC00_BoxBase
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
public:
	FBoxBeginOverlap OnBoxBeginOverlap;
	FBoxEndOverlap	OnBoxEndOverlap;
	FBoxBeginRandomLightColor OnBoxBeginRandomLightColor;
};
