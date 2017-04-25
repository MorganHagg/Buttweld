// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Rock.h"
#include "Ammo.h"
#include "Candy.h"
#include "Coin.h"
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
	void Lure();
	void IncreaseViking();
	void DecreaseViking();
	void IncreaseCoin();

	// Rotates Marve towards cursor rotation
	void RotateWithMouse();

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
	UPROPERTY(EditAnywhere)
		float Speed = 200.0f;

	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 AmmoCount = 10;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 CoinCount = 0;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 WinAmmount = 30;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		int32 EnemyCount = 0;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		bool GameWon;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		bool GameLost;
};
