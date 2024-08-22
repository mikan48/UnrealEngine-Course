// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include <GameFramework/Character.h>

ASTeleportProjectile::ASTeleportProjectile()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 5000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

void ASTeleportProjectile::Teleport_TimeElapsed()
{
	APawn* Player = AActor::GetInstigator();
	FVector ProjectileVector = GetActorLocation();
	FRotator ProjectileRotator = GetActorRotation();

	Player->SetActorLocationAndRotation(ProjectileVector, ProjectileRotator);

	Destroy();
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportAttack, this, &ASTeleportProjectile::Teleport_TimeElapsed, 0.2f);
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
