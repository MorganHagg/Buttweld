#pragma once

#include "GameFramework/Actor.h"
#include "VikingSpawner.generated.h"

UCLASS()
class DEFENDERTROLL_API AVikingSpawner : public AActor
{
	GENERATED_BODY()

public:
	AVikingSpawner();


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void GameWon();
	bool IsGameWon;

	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class ALitenViking> LitenVikingEnemy;

	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class AStorViking> StorVikingEnemy;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	// Minimum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeLow = 1.0f;

	// Maximum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeHigh = 5.0f;

	// TypeSpawner defines what type of mob is spawned. 1 = LitenViking, 2 = StorViking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		int TypeSpawner = 1;

	// Whether or not spawning is enabled
	bool bSpawningEnabled;

	// Calculates a random spawn delay
	float GetRandomSpawnDelay();

	// The current spawn delay
	float SpawnDelay;

	// The timer for when to spawn the pickup
	float SpawnTime;
};
