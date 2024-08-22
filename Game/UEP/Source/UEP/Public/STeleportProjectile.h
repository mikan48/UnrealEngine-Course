// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "STeleportProjectile.generated.h"

UCLASS()
class UEP_API ASTeleportProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:
	ASTeleportProjectile();

protected:

	FTimerHandle TimerHandle_TeleportAttack;

	void Teleport_TimeElapsed();


	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
