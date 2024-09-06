// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"
#include <Components/SphereComponent.h>

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	RespawnCooldown = 10.0f;
}

void ASPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{

}

void ASPowerUpActor::HidePowerUp()
{
	RootComponent->SetHiddenInGame(true);
}


