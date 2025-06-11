// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include <SWorldUserWidget.h>
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASAICharacter::ASAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	TimeToHitParamName = "TimeToHit";

	TargetActorKey = "TargetActor";
}



void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
	AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{

		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}

		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}

		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		//dead
		if (NewHealth <= 0.0f)
		{
			//stop BT
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				//BrainComponent - base of BT
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			//ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			SetLifeSpan(10.0f);
		}
	}
}

void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}
}

AActor* ASAICharacter::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject(TargetActorKey));
	}
	return nullptr;
}

void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
	// Ignore if target already set
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);

		USWorldUserWidget* NewWidget = CreateWidget<USWorldUserWidget>(GetWorld(), SpottedWidgetClass);
		if (NewWidget)
		{
			NewWidget->AttachedActor = this;
			// Index of 10 (or anything higher than default of 0) places this on top of any other widget.
			// May end up behind the minion health bar otherwise.
			NewWidget->AddToViewport(10);
		}
	}

	//DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
}

