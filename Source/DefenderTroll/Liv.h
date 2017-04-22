// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "Coin.h"
#include "Marve.h"
#include "Liv.generated.h"

class ALitenViking;
class AStorViking;

UCLASS()
class DEFENDERTROLL_API ALiv : public AActor
{
	GENERATED_BODY()

		
public:
	// Sets default values for this actor's properties
	ALiv();

	// Defines visible properties for Liv
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	// Defines direction for Vikings
	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void RotateToCoin();
	void RotateToCandy();
	void RotateToMarve();
	void FindObjects();
	void CheckForViking();

	ACoin* CoinReference = nullptr;
	ACandy* CandyReference = nullptr;

	TArray<AActor*> FoundCoins;
	TArray<AActor*> FoundCandy;
	TArray<AActor*> FoundLitenViking;
	TArray<AActor*> FoundStorViking;

	bool CoinExist = false;
	bool CandyExist = false;
	bool Died = false;

	int NumberOfCoins;
	int NumberOfCandy;
	int NumberOfLitenViking;
	int NumberOfStorViking;

	// Initialising for collision and overlap
	UShapeComponent* CollisionBox = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor *OtherActor, UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ScareOMeter)
		float MaxScareOMeter = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ScareOMeter)
		float CurrentScareOMeter = 0.0f;

	
	UPROPERTY(EditAnywhere)
		float CalmDown = 5.0f;
	
	UPROPERTY(EditAnywhere)
		float ScareValue = 10.0f;

	UPROPERTY(EditAnywhere)
		float MinimumRadius = 100.0f;

	UPROPERTY(EditAnywhere)
		float RadiusToMarve;

	UPROPERTY(EditAnywhere)
		float ScareRadius = 100.0f;

	UPROPERTY(EditAnywhere)
		float RadiusToLitenViking;

	UPROPERTY(EditAnywhere)
		float RadiusToStorViking;

	UPROPERTY(EditAnywhere)
		float Speed = 150.0f;

	UPROPERTY(EditAnywhere)
		float StandStillMargine = 5.0f;

	bool CanWalk;
};
