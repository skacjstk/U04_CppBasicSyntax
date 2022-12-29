// Fill out your copyright notice in the Description page of Project Settings.


#include "C01_Property.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AC01_Property::AC01_Property()
	:Chalie(30)
{
	Text = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	if (Text != nullptr) {
		Text->SetText(GetName());
	}
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC01_Property::BeginPlay()
{
	Super::BeginPlay();	

	//GLog->Log("Hello World 1");
	//UE_LOG(LogTemp, Error, L"%s", TEXT("Hello World 2"));

	if (bVisible == true) {
		FString str;
		str.Append("Alpha : ");
		str.Append(FString::FromInt(Alpha));
		str.Append("\nBravo : ");
		str.Append(FString::FromInt(Bravo));
		str.Append("\nChalie : ");
		str.Append(FString::FromInt(Chalie));
		str.Append("\nDelta : ");
		str.Append(FString::FromInt(Delta));
		str.Append("\nEcho : ");
		str.Append(FString::FromInt(Echo));
		str.Append("\nFoxtrot : ");
		str.Append(FString::FromInt(Foxtrot));
		str.Append("\nGolf : ");
		str.Append(FString::FromInt(Golf));
		GLog->Log(str);
	}
}

// Called every frame
void AC01_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

