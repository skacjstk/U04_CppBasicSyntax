// Fill out your copyright notice in the Description page of Project Settings.


#include "C00_TextRenderBase.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AC00_TextRenderBase::AC00_TextRenderBase()
{
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	Text = CreateDefaultSubobject<UTextRenderComponent>("Text");
	Text->SetupAttachment(Scene);
	
	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->TextRenderColor = FColor::Black;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->SetText(FText::FromString(GetName()));
}

// Called when the game starts or when spawned
void AC00_TextRenderBase::BeginPlay()
{
	Super::BeginPlay();
	
}

