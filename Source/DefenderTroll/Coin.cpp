// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Coin.h"


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

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotationSpeed, 0.0f)*DeltaTime);
}