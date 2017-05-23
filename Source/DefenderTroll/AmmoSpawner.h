#pragma once

#include "GameFramework/Actor.h"
#include "Ammo.h"
#include "AmmoSpawner.generated.h"

UCLASS()
class DEFENDERTROLL_API AAmmoSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AAmmoSpawner();

	virtual void BeginPlay() override;	
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<class AAmmo> Ammo;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootSphere = nullptr;

	// Minimum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeLow = 1.0f;

	// Maximum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float SpawnDelayRangeHigh = 5.0f;

	// Whether or not spawning is enabled
	bool bSpawningEnabled;

	// Calculates a random spawn delay
	float GetRandomSpawnDelay();

	// The current spawn delay
	float SpawnDelay;

	// The timer for when to spawn the pickup
	float SpawnTime;
};
