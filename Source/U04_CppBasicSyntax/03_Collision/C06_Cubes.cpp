// Fill out your copyright notice in the Description page of Project Settings.


#include "C06_Cubes.h"
#include "Global.h"
#include "C05_MultiTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"


AC06_Cubes::AC06_Cubes()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeAsset(TEXT("StaticMesh'/Game/Meshes/SM_Cube.SM_Cube'"));

	for (int32 i = 0; i < 3; ++i) {
		FString name;
		name.Append("Cube");
		name.Append(FString::FromInt(i + 1));

		Cubes[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(*name));
		Cubes[i]->SetupAttachment(Scene);
		if(cubeAsset.Succeeded())
			Cubes[i]->SetStaticMesh(cubeAsset.Object);

		Cubes[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		Cubes[i]->SetSimulatePhysics(false);
	}
}

void AC06_Cubes::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC05_MultiTrigger::StaticClass(), actors);
	if (actors.Num() <= 0) return;

	AC05_MultiTrigger* multiTrigger = Cast<AC05_MultiTrigger>(actors[0]);
	if (multiTrigger == nullptr) return;
	multiTrigger->OnMultiBeginOverlap.AddUFunction(this, "OnStartFalling");

	// Dynamic material 생성후 삽입
	UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr,
		TEXT("MaterialInstanceConstant'/Game/Materials/Mat_StaticMesh.Mat_StaticMesh'"));

	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);

	for (int32 i = 0; i < 3; ++i) {
		 FTransform transform = Cubes[i]->GetComponentToWorld(); 
		 FirstLocations[i] = transform.GetLocation();

		 if (material == nullptr) continue;
			Cubes[i]->SetMaterial(0, UMaterialInstanceDynamic::Create(material, nullptr));
	}
}

void AC06_Cubes::OnStartFalling(int32 Inindex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; ++i) {	
		Cubes[i]->SetSimulatePhysics(false);
		Cubes[i]->SetWorldLocation(FirstLocations[i], false, nullptr, ETeleportType::TeleportPhysics);	
		// 이거 순서다르면, index가 같으면 되돌아오지 않더라


		UMaterialInstanceDynamic* dynamicMaterial = Cast<UMaterialInstanceDynamic>(Cubes[i]->GetMaterial(0));
		if (dynamicMaterial == nullptr) return;
		dynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor(0.3f,0.3f,0.3f));
	}
	Cubes[Inindex]->SetSimulatePhysics(true);
	UMaterialInstanceDynamic* dynamicMaterial = Cast<UMaterialInstanceDynamic>(Cubes[Inindex]->GetMaterial(0));
	if (dynamicMaterial == nullptr) return;
	dynamicMaterial->SetVectorParameterValue("BaseColor", InColor);

}


