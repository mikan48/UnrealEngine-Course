// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpActor.h"
#include "SHealingPotion.generated.h"

/**
 * 
 */
UCLASS()
class UEP_API ASHealingPotion : public ASPowerUpActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BottleMesh;

	virtual void BeginPlay() override;

public:

	ASHealingPotion();

	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual void ShowPowerUp() override;
	virtual void HidePowerUp() override;
};
