// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "AmmoSpawner.h"


// Sets default values
AAmmoSpawner::AAmmoSpawner()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = RootSphere;

	// Set a spawn delay maximum and minimum value, + random generator to spawn actor at random intervals
	SpawnDelayRangeLow;
	SpawnDelayRangeHigh;
	SpawnDelay = GetRandomSpawnDelay();
}

// Called when the game starts or when spawned
void AAmmoSpawner::BeginPlay()
{
	Super::BeginPlay();
}

float AAmmoSpawner::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

// Called every frame
void AAmmoSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	// Always add delta time to our Spawn Time
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

