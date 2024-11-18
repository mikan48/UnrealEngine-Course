// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpActor.h"
#include "SPowerUp_Credits.generated.h"

/**
 * 
 */
UCLASS()
class UEP_API ASPowerUp_Credits : public ASPowerUpActor
{
	GENERATED_BODY()
	
public:

	ASPowerUp_Credits();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
