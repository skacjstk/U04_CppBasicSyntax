// Fill out your copyright notice in the Description page of Project Settings.


#include "CRifle.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"

// Sets default values
ACRifle::ACRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));
	Mesh->SetSkeletalMesh(meshAsset.Object);

	ConstructorHelpers::FObjectFinder<UAnimMontage> grabAsset(TEXT("AnimMontage'/Game/Character/Animations/Montages/Rifle_Grab_Montage.Rifle_Grab_Montage'"));
	if(grabAsset.Succeeded())
		GrabMontage = grabAsset.Object;
	
	ConstructorHelpers::FObjectFinder<UAnimMontage> UngrabMontageAsset(TEXT("AnimMontage'/Game/Character/Animations/Montages/Rifle_UnGrab_Montage.Rifle_UnGrab_Montage'"));
	if (UngrabMontageAsset.Succeeded())
		UngrabMontage = UngrabMontageAsset.Object;

}

ACRifle* ACRifle::Spawn(UWorld* InWorld, ACharacter* InOwnerCharacter)
{
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = InOwnerCharacter;
	return InWorld->SpawnActor<ACRifle>(spawnParam);
}

void ACRifle::Equip()
{
	if (bEquipped == true) return;
	if (bEquipping == true) return;
	bEquipping = true;

	OwnerCharacter->PlayAnimMontage(GrabMontage);
}

void ACRifle::Unequip()
{
}

// Called when the game starts or when spawned
void ACRifle::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative, true) ,HolsterSocket);
}

// Called every frame
void ACRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

