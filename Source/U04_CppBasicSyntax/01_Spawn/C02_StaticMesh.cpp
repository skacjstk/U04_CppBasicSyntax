// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_StaticMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC02_StaticMesh::AC02_StaticMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(L"/Game/Meshes/SM_Cube");

	if(meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
	else
		UE_LOG(LogTemp, Error, L"%s", TEXT("StaticMesh Asset 불러오기 실패."));
}

// Called when the game starts or when spawned
void AC02_StaticMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

