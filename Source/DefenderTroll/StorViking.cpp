// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Liv.h"
#include "StorViking.h"

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
	//UE_LOG(LogTemp, Warning, TEXT("Stor Viking Spawned"));
	NumberOfViking++;
}

// Called every frame
void AStorViking::Tick(float DeltaTime)
{
	// Finds all instances of Liv, and sets the "LivReference" to the first ([0]) actor found
	TArray<AActor*> FoundActors;
	ALiv* LivReference = nullptr;
	if (LivReference == nullptr)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALiv::StaticClass(), FoundActors);
		LivReference = Cast<ALiv>(FoundActors[0]);
	}
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	FVector LivLocation = LivReference->GetActorLocation();
	RadiusToLiv = sqrt(pow((LivLocation.X - NewLocation.X), 2) + pow((LivLocation.Y - NewLocation.Y), 2));

	// Rotates the viking to Livs location
	RotateToLiv(LivReference);
	if (RadiusToLiv < MinimumRadius)
	{
		CanWalk = false;
	}
	else
	{
		CanWalk = true;
	}
	NewLocation += (MoveDirection * Speed * DeltaTime * CanWalk);
	SetActorLocation(NewLocation);
	MoveDirection = LivReference->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();
}

void AStorViking::RotateToLiv(AActor* LivReference)
{
	//ALiv* LivReference = nullptr;
	FVector LivLocation = LivReference->GetActorLocation();
	FHitResult Hit;
	bool HitResult = false;

	if (LivReference)
	{
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(LivLocation.X, LivLocation.Y, 0.0f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}

void AStorViking::HitByRock()
{
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

void AStorViking::Death()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Coin spawned"));
	GetWorld()->SpawnActor<ACoin>(Coin_BP, Location, FRotator::ZeroRotator);
	this->Destroy();
	NumberOfViking --;
}
