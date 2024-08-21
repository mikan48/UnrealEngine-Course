// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
