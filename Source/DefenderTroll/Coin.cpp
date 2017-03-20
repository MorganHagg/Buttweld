// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Coin.h"
#include "Liv.h"
#include "LitenViking.h"


// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;

	// Defines the visible component of Coins
	// TODO: Se om vi kan fikse dette
	/*OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);*/

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CoinSphere"));
	RootSphere->SetSphereRadius(80.f);
	RootComponent = RootSphere;
	RootSphere->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	// TODO: Fiks så man kan sende NumberOfCoins arrayen til Liv.cpp
	NumberOfCoins.Add(this);

	UE_LOG(LogTemp, Warning, TEXT("Spawned coin at %s - The actual location"), *GetActorLocation().ToString());

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


