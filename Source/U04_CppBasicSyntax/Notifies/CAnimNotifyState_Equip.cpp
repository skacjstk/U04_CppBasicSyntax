// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Characters/IRifle.h"
#include "Weapons/CRifle.h"


FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// MeshComp 검사
	if (MeshComp == nullptr) return;
	IIRifle* rifleInterface = Cast<IIRifle>(MeshComp->GetOwner());

	// 소켓에 붙이기 , Equipped 변수 설정
	if (rifleInterface == nullptr) return;
	rifleInterface->GetRifle()->Begin_Equip();

}
void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// MeshComp 검사
	if (MeshComp == nullptr) return;
	IIRifle* rifleInterface = Cast<IIRifle>(MeshComp->GetOwner());

	// 소켓에 붙이기 , Equipped 변수 설정
	if (rifleInterface == nullptr) return;
	rifleInterface->GetRifle()->End_Equip();
}