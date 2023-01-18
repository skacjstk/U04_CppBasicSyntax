// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class U04_CPPBASICSYNTAX_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Speed;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Direction;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		float Pitch;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bEquipped;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Animation")
		bool bAiming;
private:
	class ACharacter* OwnerCharacter;	// Pawn 이나 Character로 해도 됨. 이 프로젝트는 캐릭터가 1개

};
