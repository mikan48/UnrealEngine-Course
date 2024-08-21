// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackHole.h"

// Sets default values
ASBlackHole::ASBlackHole()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("BlackHole");
	//SphereComp->SetSimulatePhysics(true);
	RootComponent = SphereComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->Radius = 1000.0f;
	RadialForceComp->ImpulseStrength = -40000.0f;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

