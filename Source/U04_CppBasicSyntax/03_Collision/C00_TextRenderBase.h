// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C00_TextRenderBase.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API AC00_TextRenderBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC00_TextRenderBase();

protected:
	// Called when the game starts or when spawned

	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;	// RootComponent 역할의 껍데기
	virtual void BeginPlay() override;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

};
