// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "SGameModeBase.h"
#include "Net/UnrealNetwork.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100;
	Health = MaxHealth;

	Rage = 0;
	MaxRage = 100;

	SetIsReplicatedByDefault(true);
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -MaxHealth);
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::IsFulllHealth() const
{
	return Health == MaxHealth;
}

float USAttributeComponent::GetHealth() const
{
	return Health;
}

float USAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float USAttributeComponent::GetRage() const
{
	return Rage;
}

float USAttributeComponent::GetMaxRage() const
{
	return MaxRage;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;
	float NewHealth = FMath::Clamp(Health + Delta, 0, MaxHealth);

	float ActualDelta = Health - OldHealth;

	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;

		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}

		//Died
		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	//OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return !FMath::IsNearlyZero(ActualDelta);
}

bool USAttributeComponent::ApplyRageChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}

	float OldRage = Rage;
	Rage = FMath::Clamp(Rage + Delta, 0, MaxRage);
	float ActualDelta = Rage - OldRage;
	if (ActualDelta != 0.0f)
	{
		OnRageChanged.Broadcast(InstigatorActor, this, Rage, ActualDelta);
	}

	return !FMath::IsNearlyZero(ActualDelta);
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}


void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	DOREPLIFETIME(USAttributeComponent, MaxHealth);
	//DOREPLIFETIME_CONDITION(USAttributeComponent, HealthMax, COND_InitialOnly);
}

