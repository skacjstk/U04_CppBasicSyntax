// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_StaticMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC02_StaticMesh::AC02_StaticMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AC02_StaticMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

