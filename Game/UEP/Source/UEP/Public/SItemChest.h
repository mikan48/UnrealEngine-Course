// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "SItemChest.generated.h"

UCLASS()
class UEP_API ASItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	void OnActorLoaded_Implementation();

	// Sets default values for this actor's properties
	ASItemChest();

protected:

	UPROPERTY(ReplicatedUsing = "OnRep_LidOpened", BlueprintReadOnly, SaveGame) // RepNotify
	bool bLidOpened;

	UFUNCTION()
	void OnRep_LidOpened();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;


};
