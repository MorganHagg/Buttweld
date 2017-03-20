// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "LitenViking.h"
#include "Marve.h"


// Sets default values
ALitenViking::ALitenViking()
{
	// Hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	// Visible component
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALitenViking::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Enemy Spawned"));

}

// Called every frame
void ALitenViking::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotates the viking to Marves location
	RotateToMarve();
	FVector NewLocation = GetActorLocation();
	NewLocation += (MoveDirection * Speed * DeltaTime);
	SetActorLocation(NewLocation);

	MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
}

void ALitenViking::RotateToMarve()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(PlayerLocation.X, PlayerLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}
