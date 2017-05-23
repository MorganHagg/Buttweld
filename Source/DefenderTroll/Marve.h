// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Rock.h"
#include "Ammo.h"
#include "Candy.h"
#include "Coin.h"
#include "VikingSpawner.h"
#include "Marve.generated.h"

UCLASS()
class DEFENDERTROLL_API AMarve : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMarve();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Throw();
	void CandyThrow();
	void IncreaseViking();
	void DecreaseViking();
	void IncreaseCoin();
	void DestroyAllVikings();

	TArray<AActor*> FoundLitenViking;
	TArray<AActor*> FoundStorViking;
	TArray<AActor*> FoundVikingSpawner;

	int NumberOfLitenViking;
	int NumberOfStorViking;
	int NumberOfSpawner;

	// Rotates Marve towards cursor rotation
	void RotateWithMouse();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ARock> Rock_BP;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACandy> Candy_BP;

	UPROPERTY(EditAnywhere)
		float YawSpeed = 0.1f;

	UPROPERTY(EditAnywhere)
		class UDecalComponent* CursorToWorld;

	// Sets Marves movement speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 200.0f;
	
	// Sets the delay in secods, between each eligible candy-toss
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		float candyThrowDelay = 5.0f;
	
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		float TimeTillThrow;

	// Whether or not throwing candy is enabled
	bool bCandyEnabled;

	// The timer for when Marve throws a candy
	float ThrowTime;
	// DeltaTime which is passable to other functions outside Tick
	float CurrentTime;


	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 AmmoCount = 10;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 AmmoIncline = 10;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 MaxAmmo = 15;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 CoinCount = 0;
	UPROPERTY(BlueprintReadWrite)
		int32 WinAmmount = 0;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 WinAmmountLevel1 = 25;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 WinAmmountLevel2 = 40;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 EnemyCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameWon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool GameLost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Walking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isThrowing;
};
