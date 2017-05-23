// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coin.h"
#include "LitenViking.generated.h"


UCLASS()
class DEFENDERTROLL_API ALitenViking : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALitenViking();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector MoveDirection;

	void RotateToLiv(AActor* LivReference);
	void HitByRock();
	void Death();
	void GameWon();
	
	// Reads the current distance from viking to Liv (cm)
	UPROPERTY(EditAnywhere)
		float RadiusToLiv;

	// Sets the minimum distance viking will walk to Liv (cm)
	UPROPERTY(EditAnywhere)
		float MinimumRadius = 100.0f;

	//Sets the error-margine to avoid stuttering due to Liv being unable to find the exact locations of destinations
	UPROPERTY(EditAnywhere)
		float StandStillMargine = 5.0f;

	// Sets the movement speed of Vikings
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Health = 2;
	
	// Sets the damage viking takes from rocks
	UPROPERTY(EditAnywhere)
		int DamageByRock = 1;

	bool CanWalk;

	///Får ikke dette til å funke, fordi "TimeOfDeath" oppdateres kontinuerlig
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeathAnimationTimer = 1.0f;
	float CurrentTime;
	float TimeOfDeath;*/
	UPROPERTY(BlueprintReadWrite)
		bool isDead;

};