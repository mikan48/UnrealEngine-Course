// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"

class USWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEP_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();

	// Sets default values for this component's properties
	USInteractionComponent();

protected:

	// Reliable - Will always arrive, eventually. Request will be re-sent unless an acknowledgment was received.
	// Unreliable - Not guaranteed, packet can get lost and won't retry.

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);

	// Called when the game starts
	virtual void BeginPlay() override;

	void FindBestInteractable();

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	USWorldUserWidget* DefaultWidgetInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
