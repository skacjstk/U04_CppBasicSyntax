// Fill out your copyright notice in the Description page of Project Settings.


#include "CPhysicsCube.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACPhysicsCube::ACPhysicsCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(L"/Game/Meshes/SM_Cube");

	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
	else
		UE_LOG(LogTemp, Error, L"%s", TEXT("StaticMesh Asset 불러오기 실패."));

	Mesh->SetRelativeScale3D(FVector(0.75f));
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);	// Cpp에선 오브젝트 타입도 그냥 채널: BP에선 visible, camera에나 있던 건데
}

// Called when the game starts or when spawned
void ACPhysicsCube::BeginPlay()
{
	Super::BeginPlay();
	
}

