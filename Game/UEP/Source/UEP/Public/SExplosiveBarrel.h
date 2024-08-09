// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;


UCLASS()
class UEP_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
