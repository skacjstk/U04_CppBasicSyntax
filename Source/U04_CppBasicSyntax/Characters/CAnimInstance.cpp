// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"
#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "Characters/IRifle.h"
#include "Weapons/CRifle.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());	// 역시 포인터를 넣으면 안댐
	
}
void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter == nullptr) return;
	Speed = OwnerCharacter->GetVelocity().Size2D();

	
	IIRifle* rifleInterface = Cast<IIRifle>(OwnerCharacter);
	if (!!rifleInterface) {
		bEquipped = rifleInterface->GetRifle()->IsEquipped();	// 이 부분도 Null Check 해야 함
	}
	
}
