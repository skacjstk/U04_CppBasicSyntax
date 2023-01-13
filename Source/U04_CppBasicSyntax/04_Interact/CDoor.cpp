// Fill out your copyright notice in the Description page of Project Settings.


#include "CDoor.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"

ACDoor::ACDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Components
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	RootComponent = Scene;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrame");
	DoorFrame->SetupAttachment(Scene);

	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	Door->SetupAttachment(DoorFrame);

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Scene);

	//Component Settings
	ConstructorHelpers::FObjectFinder<UStaticMesh> doorFrameAsset(TEXT("StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'"));
	if (doorFrameAsset.Succeeded())
		DoorFrame->SetStaticMesh(doorFrameAsset.Object);

	ConstructorHelpers::FObjectFinder<UStaticMesh> doorAsset(TEXT("StaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'"));
	if (doorAsset.Succeeded())
		Door->SetStaticMesh(doorAsset.Object);

	Door->SetRelativeLocation(FVector(0, 45, 0));

	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetBoxExtent(FVector(100, 50, 100));
	Box->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void ACDoor::BeginPlay()
{
	Super::BeginPlay();	
	Box->SetHiddenInGame(bHiddenCollision);

	OnActorBeginOverlap.AddDynamic(this, &ACDoor::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACDoor::ActorEndOverlap);

	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!!player)
	{
		player->OnInteractEvent.AddDynamic(this, &ACDoor::Interact);
	}
}

void ACDoor::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = Cast<ACPlayer>(OtherActor);
	if (!!Player)
	{

	}
}

void ACDoor::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = nullptr;
}

void ACDoor::Interact()
{
	if (Player == nullptr) return;
	
	UCameraComponent* cameraComp = Cast<UCameraComponent>(Player->GetComponentByClass(UCameraComponent::StaticClass()));
	if (cameraComp == nullptr) return;
	
	float dot = GetActorForwardVector() | cameraComp->GetForwardVector();
	Direction = FMath::Sign(dot);	// 음수면 -1로, 양수면 1로 

	DirectionMaxDegree = Direction* MaxDegree;

	bClosing = bOpening = bClosed;// 아래의 If문을 대체함
	bClosing = !bClosing;
	bClosed = !bClosed;

	/*
	if (bClosed)	// 닫혀있었던 경우
	{
		bOpening = true;
		bClosing = false;	// 닫아야지
	}
	else // 열려있었던 경우
	{
		bOpening = false;
		bClosing = true;	// 닫아야지
	}

	bClosed = !bClosed;
	*/


	SetActorTickEnabled(true);	// 틱 설정하기
	
}

// Called every frame
void ACDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 문의 yaw 회전이 ( 0 ~ DirectionMaxDegree )
	if (bOpening) 
	{
		YawPerTick = Direction * Speed * DeltaTime;
		Door->AddRelativeRotation(FRotator(0, YawPerTick, 0));

		// 각도가 비슷해지면 그만열려
		if (FMath::IsNearlyEqual(Door->GetRelativeRotation().Yaw, DirectionMaxDegree, 1.f))
		{
			bOpening = false;
			Door->SetRelativeRotation(FRotator(0, DirectionMaxDegree, 0));

	//		SetActorTickEnabled(false);	// 틱을 꺼버리기 ( Interact 함수가 무사실행되면 켜짐)			
		}
	}

	// 문의 yaw 회전이 ( DirectionMaxDegree ~ 0 )
	if (bClosing)	
	{
		YawPerTick = Direction * Speed * DeltaTime;
		Door->AddRelativeRotation(FRotator(0, -YawPerTick, 0));	// Add 값을 - 로 

		// IsNearlyZero  
		if (FMath::IsNearlyZero(Door->GetRelativeRotation().Yaw, 1.f))
		{
			bClosing = false;
			Door->SetRelativeRotation(FRotator::ZeroRotator);

		//	SetActorTickEnabled(false);	// 틱을 꺼버리기 ( Interact 함수가 무사실행되면 켜짐)			
		}
	}

}

