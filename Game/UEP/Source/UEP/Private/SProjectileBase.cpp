// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectileBase.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
//#include "Camera/CameraShake.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASProjectileBase::ASProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp->OnComponentHit.AddDynamic(this, &ASProjectileBase::OnActorHit);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	//ImpactShakeInnerRadius = 250.0f;
	//ImpactShakeOuterRadius = 2500.0f;

	SetReplicates(true);
}

//void ASProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	Explode();
//}
//
//// _Implementation from it being marked as BlueprintNativeEvent
//void ASProjectileBase::Explode_Implementation()
//{
//	// Check to make sure we aren't already being 'destroyed'
//	// Adding ensure to see if we encounter this situation at all
//	if (ensure(!IsPendingKill()))
//	{
//		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
//
//		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
//
//		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);
//
//		Destroy();
//	}
//}

