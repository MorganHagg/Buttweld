// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Candy.h"


// Sets default values
ACandy::ACandy()
{
 	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));
	RootComponent = CollisionBox;
	CollisionBox->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void ACandy::BeginPlay()
{
	Super::BeginPlay();

	FHitResult Hit;
	FVector CursorLocation;
	bool HitResult = false;
	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);
	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		if (CursorToWorld)
		{
			CursorToWorld->SetWorldLocation(Hit.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
		CursorLocation = Hit.Location;
		CandyDestination = FVector(CursorLocation.X, CursorLocation.Y, 0.0f);
	}
	FVector CurrentLocation = GetActorLocation();

	// Calculates the distance between spawnpoint and cursor location at spawn-time
	ThrowDistance = sqrt(pow((CursorLocation.X - CurrentLocation.X), 2) + pow((CursorLocation.Y - CurrentLocation.Y), 2));
}

// Called every frame
void ACandy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	NewLocation.Z = 0.0f;
	SetActorLocation(NewLocation);
	DistanceTraveled += Speed * DeltaTime;

	// Stops the candy when it reaches its destination, and adds rotation to make it spinn
	if (DistanceTraveled >= ThrowDistance)
	{
		Speed = 0.0f;
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed, 0.0f)*DeltaTime);
	}
}