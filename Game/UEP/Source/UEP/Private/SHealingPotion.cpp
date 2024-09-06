// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealingPotion.h"

ASHealingPotion::ASHealingPotion()
{
	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	BottleMesh->SetupAttachment(RootComponent);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnCooldown, this, &ASHealingPotion::HidePowerUp, RespawnCooldown);
}

void ASHealingPotion::BeginPlay()
{
	Super::BeginPlay();
}

void ASHealingPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASHealingPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

void ASHealingPotion::ShowPowerUp()
{
}

void ASHealingPotion::HidePowerUp()
{
	RootComponent->SetHiddenInGame(true);
}
