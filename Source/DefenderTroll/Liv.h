// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coin.h"
#include "Marve.h"
#include "Liv.generated.h"

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

	virtual void RotateToCoin();
	virtual void RotateToCandy();

	ACoin* CoinReference;
	ACandy* CandyReference;
	TArray<AActor*> FoundCoins;
	TArray<AActor*> FoundCandy;

	bool CoinExist = false;
	bool CandyExist = false;
	bool Died = false;

	int NumberOfCoins;
	int NumberOfCandy;
	// Initialising for collision and overlap
	UShapeComponent* CollisionBox = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor *OtherActor, UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = NumberOfViking)
		int32 ScareOMeter = 50;
	UPROPERTY(EditAnywhere)
		int32 CalmDown = 10;
	UPROPERTY(EditAnywhere)
		int32 ScareValue = 10;

private:
	UPROPERTY(EditAnywhere)
		float Speed = 150.f;
};
