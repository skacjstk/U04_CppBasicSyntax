// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"


// Sets default values
ACBullet::ACBullet()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");

	// StaticMesh 넣기
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/Meshes/SM_Sphere.SM_Sphere'"));
	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);

	Mesh->SetCollisionProfileName("NoCollision");
	Mesh->SetRelativeScale3D(FVector(1.0f,0.025f,0.025f));
	// 머티리얼 넣기
	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> materialAsset(TEXT("MaterialInstanceConstant'/Game/Materials/Mat_Bullet_Inst.Mat_Bullet_Inst'"));
	if (materialAsset.Succeeded())
		Mesh->SetMaterial(0, materialAsset.Object);

	Projectile->InitialSpeed = 2e+4;
	Projectile->MaxSpeed = 2e+4;
	Projectile->ProjectileGravityScale = 0.f;



}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(3.0f);
}
