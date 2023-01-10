// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Collision/C00_TextRenderBase.h"
#include "C06_Cubes.generated.h"

/**
 * 
 */
UCLASS()
class U04_CPPBASICSYNTAX_API AC06_Cubes : public AC00_TextRenderBase
{
	GENERATED_BODY()
public:
	AC06_Cubes();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Cubes[3];
		FVector FirstLocations[3];
	UFUNCTION()
		void OnStartFalling(int32 Inindex, FLinearColor InColor);

private:
	class UMaterialInstanceDynamic* DynamicMaterial;
};
