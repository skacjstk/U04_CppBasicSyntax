// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_DrawDebug.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API AC02_DrawDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC02_DrawDebug();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "DrawDebug")
		FVector RelativeLocation[4];

	FVector WorldLocation[4];
};
