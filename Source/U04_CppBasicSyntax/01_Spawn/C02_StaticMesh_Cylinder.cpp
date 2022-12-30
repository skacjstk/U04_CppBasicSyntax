// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_StaticMesh_Cylinder.h"

AC02_StaticMesh_Cylinder::AC02_StaticMesh_Cylinder()
{
//	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
//	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(L"/Game/Meshes/SM_Cylinder");

	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
	else
		UE_LOG(LogTemp, Error, L"%s", TEXT("StaticMesh Asset 불러오기 실패."));
}