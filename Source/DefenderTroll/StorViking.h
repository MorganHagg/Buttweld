// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coin.h"
#include "StorViking.generated.h"

UCLASS()
class DEFENDERTROLL_API AStorViking : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStorViking();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Defines visible properties for Liten Viking
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACoin> Coin_BP;

	// Defines direction for Vikings
	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	virtual void RotateToLiv(AActor* LivReference);
	virtual void HitByRock();
	virtual void Death();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NumberOfViking)
		int32 NumberOfViking;
private:
	// Defines the movement speed of Vikings
	UPROPERTY(EditAnywhere)
		float RadiusToLiv;

	UPROPERTY(EditAnywhere)
		float MinimumRadius = 100.0f;

	UPROPERTY(EditAnywhere)
		float StandStillMargine = 5.0f;

	UPROPERTY(EditAnywhere)
		float Speed = 150.f;

	UPROPERTY(EditAnywhere)
		int Health = 120;

	UPROPERTY(EditAnywhere)
		int DamageByRock = 50;

	bool CanWalk;
};