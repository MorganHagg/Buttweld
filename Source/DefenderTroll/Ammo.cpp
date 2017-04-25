// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Ammo.h"


// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AmmoSphere"));
	RootSphere->SetSphereRadius(SphereRadius);
	RootComponent = RootSphere;
	RootSphere->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAmmo::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}