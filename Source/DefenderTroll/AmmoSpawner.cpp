#include "DefenderTroll.h"
#include "AmmoSpawner.h"

AAmmoSpawner::AAmmoSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;

	// Set a spawn delay maximum and minimum value, + random generator to spawn actor at random intervals
	SpawnDelayRangeLow;
	SpawnDelayRangeHigh;
	SpawnDelay = GetRandomSpawnDelay();
}

void AAmmoSpawner::BeginPlay()
{
	Super::BeginPlay();
}

float AAmmoSpawner::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

void AAmmoSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	// Always add deltatime to our Spawn Time
	SpawnTime += DeltaTime;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);
	if (bShouldSpawn)
	{
		//Deduct spawn delay from accumulated time value
		SpawnTime -= SpawnDelay;
		SpawnDelay = GetRandomSpawnDelay();
		
		FVector Location = GetActorLocation();
		GetWorld()->SpawnActor<AAmmo>(Ammo, Location, FRotator::ZeroRotator);
	}
}

