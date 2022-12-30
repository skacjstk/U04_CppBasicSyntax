// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C02_Spawner.generated.h"

UCLASS()
class U04_CPPBASICSYNTAX_API AC02_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC02_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
		UClass* classRef;	// 클래스 레퍼런스를 저장할 수 있는 변수

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC02_Static_Mesh> TsubclassRef;	// 특정 자식으로만 제한할 수 있는 변수

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AC02_Static_Mesh> SpawnClasses[4];


	class AC02_StaticMesh* Meshes[4];
};
