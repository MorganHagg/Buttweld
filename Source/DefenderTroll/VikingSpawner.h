// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "VikingSpawner.generated.h"

UCLASS()
class DEFENDERTROLL_API AVikingSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVikingSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class ALitenViking> MyEnemyClass;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	/** Minimum spawn delay*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeLow = 1.0f;

	/** Maximum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeHigh = 5.0f;

	/** Whether or not spawning is enabled */
	bool bSpawningEnabled;

	/** Calculates a random spawn delay */
	float GetRandomSpawnDelay();

	/** The current spawn delay */
	float SpawnDelay;

	/** The timer for when to spawn the pickup */
	float SpawnTime;

	// Sets a maximum value to how many vikings can be spawned
	int numberOfViking;
	int maxNumberOfSpawn;

};
