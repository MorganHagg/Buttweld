#include "DefenderTroll.h"
#include "VikingSpawner.h"
#include "StorViking.h"
#include "LitenViking.h"

AVikingSpawner::AVikingSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;

	// Set a spawn delay maximum and minimum value, + random generator to spawn actor at random intervals
	SpawnDelayRangeLow;
	SpawnDelayRangeHigh;
	SpawnDelay = GetRandomSpawnDelay();
}

void AVikingSpawner::BeginPlay()
{
	Super::BeginPlay();
}

float AVikingSpawner::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}


void AVikingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTime += DeltaTime;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);

	if (bShouldSpawn && !IsGameWon)
	{
		// TypeSpawner == 1 sets the spawner to spawn LitenViking
		if (TypeSpawner == 1)
		{
			//Deduct spawn delay from accumulated time value
			SpawnTime -= SpawnDelay;
			SpawnDelay = GetRandomSpawnDelay();

			FVector Location = GetActorLocation();
			GetWorld()->SpawnActor<ALitenViking>(LitenVikingEnemy, Location, FRotator::ZeroRotator);
		}
		// TypeSpawner == 2 sets the spawner to spawn StorViking
		if (TypeSpawner == 2)
		{
			//Deduct spawn delay from accumulated time value
			SpawnTime -= SpawnDelay;
			SpawnDelay = GetRandomSpawnDelay();

			FVector Location = GetActorLocation();
			GetWorld()->SpawnActor<AStorViking>(StorVikingEnemy, Location, FRotator::ZeroRotator);
		}
	}
}

void AVikingSpawner::GameWon()
{
	IsGameWon = true;
}