// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealingPotion.h"
#include <SAttributeComponent.h>

ASHealingPotion::ASHealingPotion()
{
	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	BottleMesh->SetupAttachment(RootComponent);

	AmountOfHeal = 50;
}

void ASHealingPotion::BeginPlay()
{
	Super::BeginPlay();

	//HidePowerUp();
}

void ASHealingPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASHealingPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	AttributeComp->ApplyHealthChange(AmountOfHeal);

	HidePowerUp();
}
