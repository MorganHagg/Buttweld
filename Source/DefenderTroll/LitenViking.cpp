// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Liv.h"
#include "LitenViking.h"

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
	Cast<AMarve>(GetWorld()->GetFirstPlayerController()->GetPawn())->IncreaseViking();
	isDead = false;
}

// Called every frame
void ALitenViking::Tick(float DeltaTime)
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
	// Stops the viking from walking if it's too close to Liv
	if (!isDead)
	{
		if (RadiusToLiv < MinimumRadius)
		{
			CanWalk = false;
		}
		else
		{
			CanWalk = true;
		}
	}
	NewLocation += (MoveDirection * Speed * DeltaTime * CanWalk);
	SetActorLocation(NewLocation);
	MoveDirection = LivReference->GetActorLocation() - GetActorLocation();
	MoveDirection.Normalize();

	///Får ikke dette til å funke, fordi "TimeOfDeath" oppdateres kontinuerlig
	//CurrentTime += DeltaTime;
	//if (isDead == true)
	//{
	//	CanWalk = false;
	//	if ((DeltaTime - TimeOfDeath) > DeathAnimationTimer)
	//	{
	//		this->Destroy();
	//	}
	//}
}

void ALitenViking::RotateToLiv(AActor* LivReference)
{
	FVector LivLocation = LivReference->GetActorLocation();
	if (LivReference)
	{
		FVector TempLocation = FVector(LivLocation.X, LivLocation.Y, 0.0f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
}

void ALitenViking::HitByRock()
{	
	if (Health > 0)
	{
		Health = Health - DamageByRock;
	}
	 if (Health <= 0 && (!isDead))
	{
		 ///Får ikke dette til å funke, fordi "TimeOfDeath" oppdateres kontinuerlig
		 //TimeOfDeath = CurrentTime;
		 Death();
	}
}

void ALitenViking::Death()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Coin spawned"));
	GetWorld()->SpawnActor<ACoin>(Coin_BP, Location, FRotator::ZeroRotator);
	isDead = true;
	Cast<AMarve>(GetWorld()->GetFirstPlayerController()->GetPawn())->DecreaseViking();
}

void ALitenViking::GameWon()
{
	this->Destroy();
}
