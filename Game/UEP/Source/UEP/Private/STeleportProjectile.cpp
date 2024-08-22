// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include <GameFramework/Character.h>
#include "GameFramework/ProjectileMovementComponent.h"

ASTeleportProjectile::ASTeleportProjectile()
{
	MovementComp->InitialSpeed = 6000.0f;
}

void ASTeleportProjectile::Teleport_TimeElapsed()
{
	//clear timer 
	GetWorldTimerManager().ClearTimer(TimerHandle_TeleportAttack);

	APawn* Player = AActor::GetInstigator();
	FVector ProjectileVector = GetActorLocation();
	FRotator ProjectileRotator = GetActorRotation();

	//there is also Player->TeleportTo(...)
	Player->SetActorLocationAndRotation(ProjectileVector, ProjectileRotator);

	Destroy();
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_TeleportAttack, this, &ASTeleportProjectile::Teleport_TimeElapsed, TeleportDelay);
}

void ASTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
