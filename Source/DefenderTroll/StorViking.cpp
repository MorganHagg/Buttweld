// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "StorViking.h"
#include "Marve.h"
#include "Coin.h"
#include "Liv.h"

// Sets default values
AStorViking::AStorViking()
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
void AStorViking::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Enemy Spawned"));

	// Finds all instances of Liv, and sets the "LivReference" to the first ([0]) actor found
	// TODO Lage en For-loop som leter etter liv, i tilfelle liv (av en grunn) ikke er [0]
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALiv::StaticClass(), FoundActors);
	LivReference = Cast<ALiv>(FoundActors[0]);

}

// Called every frame
void AStorViking::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotates the viking to Marves location
	//RotateToMarve();

	// Rotates the viking to Livs location
	RotateToLiv();
	FVector NewLocation = GetActorLocation();
	NewLocation += (MoveDirection * Speed * DeltaTime);
	SetActorLocation(NewLocation);

	MoveDirection = LivReference->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
}



void AStorViking::RotateToLiv()
{
	FVector LivLocation = LivReference->GetActorLocation();
	FHitResult Hit;
	bool HitResult = false;

	if (LivReference)
	{
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(LivLocation.X, LivLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}

void AStorViking::RotateToMarve()
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

void AStorViking::HitByRock()
{
	// Spawn of coin shall later be under Death();
	UWorld* World = GetWorld();
	if (Health > 0)
	{
		Health = Health - DamageByRock;
	}
	if (Health < 1)
	{
		Death();
	}

}
void AStorViking::HitByMelee()
{
	// Spawn of coin shall later be under Death();
	UWorld* World = GetWorld();
	if (Health > 0)
	{
		Health = Health - DamageByMelee;
	}
	if (Health < 1)
	{
		Death();
	}

}

void AStorViking::Death()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Coin spawned"));
	GetWorld()->SpawnActor<ACoin>(Coin_BP, Location, FRotator::ZeroRotator);
	this->Destroy();
}
