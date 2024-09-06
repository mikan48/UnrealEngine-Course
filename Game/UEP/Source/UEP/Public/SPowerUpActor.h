// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerUpActor.generated.h"

class USphereComponent;

UCLASS(ABSTRACT)
class UEP_API ASPowerUpActor : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float RespawnCooldown;


	// Sets default values for this actor's properties
	ASPowerUpActor();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComp;

	FTimerHandle TimerHandle_RespawnCooldown;

	virtual void ShowPowerUp();
	virtual void HidePowerUp();

};
