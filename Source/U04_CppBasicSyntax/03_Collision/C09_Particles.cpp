// Fill out your copyright notice in the Description page of Project Settings.


#include "C09_Particles.h"
#include "Global.h"
#include "particles/ParticleSystem.h"
#include "C08_EventTrigger.h"

AC09_Particles::AC09_Particles()
{
	ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset1(TEXT("ParticleSystem'/Game/Explosions/Particles/P_ImpactExplosion2.P_ImpactExplosion2'"));
	if (particleAsset1.Succeeded())
		Particles[0] = particleAsset1.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset2(TEXT("ParticleSystem'/Game/Particles/P_Impact_Fireball.P_Impact_Fireball'"));
	if (particleAsset2.Succeeded())
		Particles[1] = particleAsset2.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset3(TEXT("ParticleSystem'/Game/Particles/P_Impact_ThunderBall.P_Impact_ThunderBall'"));
	if (particleAsset3.Succeeded())
		Particles[2] = particleAsset3.Object;
}

void AC09_Particles::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC08_EventTrigger::StaticClass(), actors);
	if (actors.Num() < 1) return;
	AC08_EventTrigger* eventTrigger = Cast< AC08_EventTrigger>(actors[0]);
	if (eventTrigger == nullptr) return;

	eventTrigger->OnDelegate.AddUFunction(this, "PlayRandomParticle");

}

void AC09_Particles::PlayRandomParticle(int32 InIndex)
{
	FTransform transform;
	transform.SetLocation(GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], transform);

	//sizeof(Particles)/sizeof(Particles[0])
}
