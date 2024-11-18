// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealingPotion.h"
#include <SAttributeComponent.h>
#include <SPlayerState.h>

ASHealingPotion::ASHealingPotion()
{
	BottleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottleMesh"));
	BottleMesh->SetupAttachment(RootComponent);

	AmountOfHeal = 50;

	CreditCost = 50;
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
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (ensure(AttributeComp) && !AttributeComp->IsFulllHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, AttributeComp->GetMaxHealth()))
			{
				HidePowerUp();
			}
		}
	}
}
