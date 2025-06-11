// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpActor.h"
#include <Components/SphereComponent.h>
#include <SAttributeComponent.h>
#include <SPlayerState.h>

// Sets default values
ASPowerUpActor::ASPowerUpActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	RespawnCooldown = 10.0f;

	SetReplicates(true);
}

//void ASPowerUpActor::BeginPlay()
//{
//	Super::BeginPlay();
//
//	HidePowerUp();
//}

void ASPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{

}

void ASPowerUpActor::ShowPowerUp()
{
	RootComponent->SetVisibility(true, true);
}

void ASPowerUpActor::HidePowerUp()
{
	RootComponent->SetVisibility(false, true);

	FTimerHandle TimerHandle_RespawnCooldown;
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnCooldown, this, &ASPowerUpActor::ShowPowerUp, RespawnCooldown);
}

