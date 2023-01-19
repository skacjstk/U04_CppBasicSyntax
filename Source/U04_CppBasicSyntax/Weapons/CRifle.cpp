

#include "CRifle.h"
#include "Global.h"
#include "Characters/IRifle.h"
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

	OwnerCharacter->PlayAnimMontage(GrabMontage, 1.75f);
}

void ACRifle::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative,true), HandSocket);
}

void ACRifle::End_Equip()
{
	bEquipping = false;

}

void ACRifle::Begin_Unequip()
{
	bEquipped = false;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);

}

void ACRifle::End_Unequip()
{
	bEquipping = false;
}

void ACRifle::Unequip()
{
	if (bEquipped == false) return;
	if (bEquipping == true) return;
	bEquipping = true;

	OwnerCharacter->PlayAnimMontage(UngrabMontage, 1.75f);
}

void ACRifle::BeginAiming()
{
	bAiming = true;
}

void ACRifle::EndAiming()
{
	bAiming = false;	
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

	// OnAim 일 때 표적판 마우스 대면 위젯.Dot을 빨간색으로
	if (bAiming == false) return;

	IIRifle* rifleInterface = Cast<IIRifle>(OwnerCharacter);
	if (rifleInterface == nullptr) return;
	FVector aimInfo[3];
	rifleInterface->GetAimInfo(aimInfo[0], aimInfo[1], aimInfo[2]);
	
	//DrawDebugLine(GetWorld(), aimInfo[0], aimInfo[1], FColor::Red, false, -1.f, 0, 3.f);

	FHitResult hitResult;
	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.AddIgnoredActor(this);
	collisionQueryParams.AddIgnoredActor(OwnerCharacter);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, aimInfo[0], aimInfo[1], ECollisionChannel::ECC_PhysicsBody, collisionQueryParams))
	{
		//Todo: 라인에 닿았으면 Owner->OnTarget 호출 외 여러개
		// 충돌은 다른 곳에 할 것
	}




}

