// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Liv.h"
#include "Coin.h"

// Sets default values
ALiv::ALiv()
{
	// Hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));

	// Visible component
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALiv::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ALiv::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += (MoveDirection * Speed * DeltaTime);
	SetActorLocation(NewLocation);

	// Finds all instances of Coin, and sets the "CoinReference" to the array of coins found
	if (CoinReference)
	{
		MoveDirection = CoinReference->GetActorLocation() - GetActorLocation();
		MoveDirection.Normalize();
	}
	else
	{
		/*for (int i = 30; i >= 0; i--)
		{
			CoinReference = Cast<ACoin>(NumberOfCoins[i]);
		}*/
		UE_LOG(LogTemp, Warning, TEXT("Liv didn't find a coin"));
	}


}

void ALiv::RotateToCoin()
{
	FVector CoinLocation = CoinReference->GetActorLocation();
	FHitResult Hit;
	bool HitResult = false;


	if (CoinReference)
	{
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(CoinLocation.X, CoinLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}

/*

Kode for å få beveget Liv til coin[i] - Funker nesten

for (int i = 0; i <= 2; i++)
{
UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), FoundActors);
CoinReference = Cast<ACoin>(FoundActors[i]);
UE_LOG(LogTemp, Error, TEXT("For loop ran"));
}

*/