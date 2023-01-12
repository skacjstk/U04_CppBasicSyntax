// Fill out your copyright notice in the Description page of Project Settings.


#include "C13_Explosion.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Particles/ParticleSystemComponent.h"



AC13_Explosion::AC13_Explosion()
{
	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetupAttachment(Scene);

	ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("ParticleSystem'/Game/Particles/P_Impact_FireBall.P_Impact_FireBall'"));
	if(particleAsset.Succeeded())
		Particle->SetTemplate(particleAsset.Object);
	(*Particle).bAutoActivate = false;
}

void AC13_Explosion::OnExplosion(AActor* OverlappedActor, AActor* OtherActor)
{
	if (Cast<ACPlayer>(OtherActor) == nullptr) return;
	//Sphere Trace
	FVector start = GetActorLocation();
	FVector end = FVector(start.X+ 500, start.Y, start.Z);

	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hitResults;

	objectTypes.Add(EObjectTypeQuery::ObjectTypeQuery4);

	if (UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		start,
		end,	// 이거 굳이 안그래도 된다.
		100,
		objectTypes,
		false,
		ignoreActors,
		EDrawDebugTrace::ForDuration,
		hitResults,
		true
	))
	{
		// 파티클 재생
		Particle->ResetParticles();
		Particle->SetActive(true);
		// Radial Impulse

		for (const FHitResult& hitResult : hitResults) {
			UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (!!meshComp) {
				meshComp->AddRadialImpulse(start, 1000, 15e6 / meshComp->GetMass(), ERadialImpulseFalloff::RIF_Linear);
			}
				

		} // end for
	}//end if
}
