// Fill out your copyright notice in the Description page of Project Settings.


#include "C04_TwoLights.h"
#include "Global.h"
#include "C03_LightTrigger.h"
#include "Components/PointLightComponent.h"

AC04_TwoLights::AC04_TwoLights()
{
	PointLight1 = CreateDefaultSubobject<UPointLightComponent>("PointLight1");
	PointLight1->SetupAttachment(Scene);

	PointLight2 = CreateDefaultSubobject<UPointLightComponent>("PointLight2");
	PointLight2->SetupAttachment(Scene);

	PointLight1->Intensity = 1e+4f;
	PointLight1->AttenuationRadius = 200.0f;
	PointLight1->LightColor = FColor(255, 128, 50);

	PointLight2->Intensity = 1e+4f;
	PointLight2->AttenuationRadius = 200.0f;
	PointLight2->LightColor = FColor(255, 128, 50);
	PointLight2->SetRelativeLocation(FVector(200, 0, 0));
}
void AC04_TwoLights::BeginPlay()
{
	Super::BeginPlay();
	PointLight1->SetVisibility(false);
	PointLight2->SetVisibility(false);

	TArray<AActor*> actors;
	// 바인딩...
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC03_LightTrigger::StaticClass(), actors);
	if (actors.Num() <= 0) return;

	AC03_LightTrigger* trigger = Cast<AC03_LightTrigger>(actors[0]);	// 참조라서 여기서 바꾸면 바뀜
	if (trigger == nullptr) return;
	
//	trigger->OnBoxBeginOverlap.BindLambda([]() { CLog::Log("Called"); });
	trigger->OnBoxBeginOverlap.BindUFunction(this, "OnLight");
//	trigger->OnBoxEndOverlap.BindUFunction(this, "OffLight");
	trigger->OnBoxEndOverlap.BindUObject(this, &AC04_TwoLights::OffLight);
	trigger->OnBoxBeginRandomLightColor.BindUFunction(this, "OnRandomColorLight");
}

void AC04_TwoLights::OnLight() 
{
	PointLight1->SetVisibility(true);
	PointLight2->SetVisibility(true);
}
void AC04_TwoLights::OffLight() 
{
	PointLight1->SetVisibility(false);
	PointLight2->SetVisibility(false);
}

FString AC04_TwoLights::OnRandomColorLight(FLinearColor InColor)
{
	PointLight2->SetLightColor(InColor);
	return InColor.ToString();
}
