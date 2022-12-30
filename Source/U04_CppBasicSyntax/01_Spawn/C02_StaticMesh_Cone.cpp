// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_StaticMesh_Cone.h"


AC02_StaticMesh_Cone::AC02_StaticMesh_Cone()
{
	//	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	//	RootComponent = Mesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshAsset(TEXT("StaticMesh'/Game/Meshes/SM_Cone.SM_Cone'"));

	if (meshAsset.Succeeded())
		Mesh->SetStaticMesh(meshAsset.Object);
	else
		UE_LOG(LogTemp, Error, L"%s", TEXT("StaticMesh Asset 불러오기 실패."));
}