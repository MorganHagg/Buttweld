// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "VikingSpawner.h"
#include "LitenViking.h"


// Sets default values
AVikingSpawner::AVikingSpawner()
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
void AVikingSpawner::BeginPlay()
{
	Super::BeginPlay();
	numberOfViking = 0;
	maxNumberOfSpawn = 10;

}

float AVikingSpawner::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}


// Called every frame
void AVikingSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO: Lage en forløkke som teller antall vikinger på banen
	// TODO: Forløkken bestemmer om spawneren skal spawne flere vikinger




	// Always add delta time to our Spawn Time
	SpawnTime += DeltaTime;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);

	if (bShouldSpawn && (numberOfViking < maxNumberOfSpawn))
	{
		UWorld* World = GetWorld();
		if (World)
		{

			//Deduct spawn delay from accumulated time value
			SpawnTime -= SpawnDelay;

			SpawnDelay = GetRandomSpawnDelay();

			FVector Location = GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("Number of Vikings increases!!"));
			numberOfViking++;
			World->SpawnActor<ALitenViking>(MyEnemyClass, Location, FRotator::ZeroRotator);
		}
	}

}
