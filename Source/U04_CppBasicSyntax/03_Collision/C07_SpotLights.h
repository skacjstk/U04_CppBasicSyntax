// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Collision/C00_TextRenderBase.h"
#include "C07_SpotLights.generated.h"

/**
 * 
 */
UCLASS()
class U04_CPPBASICSYNTAX_API AC07_SpotLights : public AC00_TextRenderBase
{
	GENERATED_BODY()
public:
	AC07_SpotLights();
protected:
	virtual void BeginPlay() override;
private:
	class USpotLightComponent* SpotLights[3];
	
private:
	UFUNCTION()
		void OnRandomLightColor(int32 InIndex, FLinearColor InColor);
};
