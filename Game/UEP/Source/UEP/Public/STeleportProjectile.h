// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "STeleportProjectile.generated.h"

UCLASS()
class UEP_API ASTeleportProjectile : public ASProjectileBase
{
	GENERATED_BODY()

public:
	ASTeleportProjectile();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay = 0.2f;

	FTimerHandle TimerHandle_TeleportAttack;

	void Teleport_TimeElapsed();


	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
