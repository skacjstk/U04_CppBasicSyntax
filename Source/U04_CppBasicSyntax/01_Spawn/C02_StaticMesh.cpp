// Fill out your copyright notice in the Description page of Project Settings.


#include "C02_StaticMesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

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
	UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, 
		TEXT("MaterialInstanceConstant'/Game/Materials/Mat_StaticMesh.Mat_StaticMesh'"));

	UMaterialInstanceConstant* material;
	// MaterialInstanceConstant'/Game/Materials/Mat_StaticMesh.Mat_StaticMesh'
	material = Cast<UMaterialInstanceConstant>(obj);
	if (material == nullptr) return;

	// 다이나믹 머티리얼 생성 코드
	DynamicMaterial = UMaterialInstanceDynamic::Create(material, nullptr);

	Mesh->SetMaterial(0, DynamicMaterial);

	UKismetSystemLibrary::K2_SetTimer(this, "ChangeParameter", 1.0f, true);	//SetTimerByFunctionName

}

void AC02_StaticMesh::ChangeParameter()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A = 1.0f;

	float metalic = UKismetMathLibrary::RandomFloatInRange(0, 1);
	float roughness = UKismetMathLibrary::RandomFloatInRange(0, 1);

	DynamicMaterial->SetVectorParameterValue("BaseColor", color);
	DynamicMaterial->SetScalarParameterValue("Metalic", metalic);
	DynamicMaterial->SetScalarParameterValue("Roughness", roughness);
	
}

