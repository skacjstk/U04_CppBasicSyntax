// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CRifle.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API ACRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACRifle();

	static ACRifle* Spawn(class UWorld* InWorld, class ACharacter* InOwnerCharacter);

	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE void ToggleAutoFire() { bAutoFire = !bAutoFire; }
	
	void Equip();

	void Begin_Equip();
	void End_Equip();

	void Begin_Unequip();
	void End_Unequip();

	void Unequip();

	void BeginAiming();
	void EndAiming();

	void Begin_Fire();
	void End_Fire();

	void Firing();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		TSubclassOf<class ACBullet> BulletClass;
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		float PitchSpeed = 0.25f;
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_Rifle";

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		class UAnimMontage* GrabMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		class UAnimMontage* UngrabMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
		TSubclassOf<class UCameraShake> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* FlashParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* EjectParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UParticleSystem* ImpactParticle;
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class USoundCue* FireSoundCue;
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		class UMaterialInstanceConstant* DecalMaterial;
private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
	class ACharacter* OwnerCharacter;
	
	float CurrentPitch;

	bool bEquipped; 	// true: OnRifle, False : OffRifle
	bool bEquipping;	// ?????? ?????? ???????????? ???
	bool bAiming;		// true: Aim ???????????? 
	bool bFiring;
	bool bAutoFire;

	FTimerHandle AutoFireTimer;
};
