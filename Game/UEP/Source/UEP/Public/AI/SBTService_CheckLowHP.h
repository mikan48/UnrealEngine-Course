// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckLowHP.generated.h"

/**
 * 
 */
UCLASS()
class UEP_API USBTService_CheckLowHP : public UBTService
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsLowKey;

	// %
	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthMarker;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
public:

	USBTService_CheckLowHP();
};
