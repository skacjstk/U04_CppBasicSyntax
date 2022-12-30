// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_Spawner.h"
#include "C02_StaticMesh.h"

// Sets default values
AC02_Spawner::AC02_Spawner()
{

}

// Called when the game starts or when spawned
void AC02_Spawner::BeginPlay()
{
	Super::BeginPlay();

	FTransform transform;
	for (int32 i = 0; i < 4; ++i) {


		Meshes[i] = GetWorld()->SpawnActor<AC02_StaticMesh>(SpawnClasses[i], transform);

//		Meshes[i]->GetActorLocation();

	}
	
}
