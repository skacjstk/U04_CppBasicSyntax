// Fill out your copyright notice in the Description page of Project Settings.


#include "Global.h"
#include "CAnimInstance.h"
#include "Characters/CPlayer.h"

void UCAnimInstance::NativeBeginPlay()
{
	Player = Cast<ACPlayer>(TryGetPawnOwner());	// 역시 포인터를 넣으면 안댐
	
}
void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Player == nullptr) return;
	Speed = Player->GetVelocity().Size2D();
	
}
