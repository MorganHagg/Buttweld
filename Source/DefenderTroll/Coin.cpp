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
	CollisionBox = CreateDefaultSubobject<USphereComponent>(TEXT("CoinSphere"));
	RootComponent = CollisionBox;
	CollisionBox->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Spawned coin at %s"), *GetActorLocation().ToString());

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::ReportPosition()
{
	UE_LOG(LogTemp, Warning, TEXT("Liv picked a coin at %s"), *GetActorLocation().ToString());
}