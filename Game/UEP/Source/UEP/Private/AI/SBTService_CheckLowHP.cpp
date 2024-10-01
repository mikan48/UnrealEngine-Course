// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHP.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <SAttributeComponent.h>

USBTService_CheckLowHP::USBTService_CheckLowHP()
{
	LowHealthMarker = 0.6f;
}

void USBTService_CheckLowHP::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
		if (ensure(AIPawn))
		{
			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIPawn);

			if (ensure(AttributeComp))
			{
				bool bIsLow = LowHealthMarker >= (AttributeComp->GetMaxHealth() / AttributeComp->GetHealth());
				BlackBoardComp->SetValueAsBool(IsLowKey.SelectedKeyName, bIsLow);
			}
		}
	}
}


