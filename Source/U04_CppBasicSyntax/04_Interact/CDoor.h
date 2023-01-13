// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoor.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API ACDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void ActorBeginOverlap(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void ActorEndOverlap(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
		void Interact();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 씬, 문, 테두리, 박스
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

private:
	UPROPERTY(EditAnywhere)
	bool bHiddenCollision = false;
	UPROPERTY(EditAnywhere)
		float MaxDegree = 90.f;
	UPROPERTY(EditAnywhere)
		float Speed = 100.f;	// 문이 열리는 속도

private:
	class ACPlayer* Player;	
	float Direction;
	float DirectionMaxDegree;	// 최종적으로 만들어진, 변화해야 할 각도 양
	float YawPerTick;

	bool bClosed = true;	// Open or Close
	bool bOpening;	// Tick 조건판단용
	bool bClosing;	// Tick 조건판단용
};
