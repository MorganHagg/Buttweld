// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Liv.h"
#include "coin.h"
#include "candy.h"
#include "StorViking.h"
#include "LitenViking.h"

// Sets default values
ALiv::ALiv()
{
	// Set this actor to call Tick() every frame.
	PrimaryActorTick.bCanEverTick = true;
	// Hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	// Visible component
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALiv::BeginPlay()
{
	Super::BeginPlay();
	//Checks if there is overlap
	CollisionBox = this->FindComponentByClass<USphereComponent>();
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALiv::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Collider"));
	}
	CoinExist = false;
	CandyExist = false;
	pickingStuff = false;
}

// TODO: Fiks bug hvor liv beveger seg bakover, om hun "unngår marve" og det spawner en coin samtidig
// Called every frame
void ALiv::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector LivDestination;
	FVector NewLocation = GetActorLocation();
	FVector MarveLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// Checks if the scare-o-meter is full. If it is, the game is lost
	if (CurrentScareOMeter >= MaxScareOMeter)
	{
		Cast<AMarve>(GetWorld()->GetFirstPlayerController()->GetPawn())->GameLost = true;
	}
	if (CurrentScareOMeter > 0)
	{
		CurrentScareOMeter = CurrentScareOMeter - CalmDown;
	}

	// Finds all coins, candies and vikings
	FindObjects();
	CheckForViking();

	// Movement logic
	if (CandyExist)
	{
		RotateToCandy();
		CanWalk = true;
		LivDestination = CandyReference->GetActorLocation();
	}
	else
	{
		if (CoinExist)
		{
			RotateToCoin();
			CanWalk = true;
			LivDestination = CoinReference->GetActorLocation();
		}
		else
		{
			RadiusToMarve = sqrt(pow((MarveLocation.X - NewLocation.X), 2) + pow((MarveLocation.Y - NewLocation.Y), 2));
			LivDestination = MarveLocation;
			RotateToMarve();
			// First checks if Liv is within Standstill radius to Marve
			// Then checks if Coin and/or Candy exists
			// If the first is true, and the second one is false, then Liv can't walk
			if (((RadiusToMarve - StandStillMargine) < MinimumRadius) && ((RadiusToMarve + StandStillMargine) > MinimumRadius) && ((!CoinExist) && (!CandyExist)))
			{
				CanWalk = false;
			}
			else
			{
				CanWalk = true;
			}
		}
	}
	NewLocation += (MoveDirection * Speed * DeltaTime * CanWalk);
	SetActorLocation(NewLocation);
	// If Liv is too close to Marve, and no coin and/or candy exist, then Livs move direction is away from Marve
	if (RadiusToMarve < MinimumRadius && ((!CoinExist) && (!CandyExist)))
	{
		MoveDirection = GetActorLocation() - LivDestination;
	}
	else
	{
		MoveDirection = LivDestination - GetActorLocation();
	}
	// Locks liv movement to X and Y plane.
	MoveDirection.Z = 0.0f;
	MoveDirection.Normalize();
}

// Checks for all vikings within a parameter to Liv. If there are any: Increase Scare-o-meter
void ALiv::CheckForViking()
{
	ALitenViking* LitenVikingReference = nullptr;
	AStorViking* StorVikingReference = nullptr;
	FVector VikingLocation;
	FVector NewLocation;
	
	// Finds all actors of LitenViking and StorViking, and counts them
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALitenViking::StaticClass(), FoundLitenViking);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorViking::StaticClass(), FoundStorViking);
	NumberOfLitenViking = FoundLitenViking.Num() - 1;
	NumberOfStorViking = FoundStorViking.Num() - 1;

	// Checks if there are any vikings to save computing power, since the calculation is demanding
	if (NumberOfLitenViking > 0)
	{
		for (int i = 0; i <= NumberOfLitenViking; i++)
		{
			NewLocation = GetActorLocation();
			LitenVikingReference = Cast<ALitenViking>(FoundLitenViking[i]);
			VikingLocation = LitenVikingReference->GetActorLocation();
			RadiusToLitenViking = sqrt(pow((VikingLocation.X - NewLocation.X), 2) + pow((VikingLocation.Y - NewLocation.Y), 2));
			if (RadiusToLitenViking < ScareRadius)
			{
				CurrentScareOMeter = CurrentScareOMeter + ScareValue;
			}
		}
	}
	// Checks if there are any vikings to save computing power, since the calculation is demanding
	if (NumberOfStorViking > 0)
	{
		for (int i = 0; i <= NumberOfStorViking; i++)
		{
			NewLocation = GetActorLocation();
			StorVikingReference = Cast<AStorViking>(FoundStorViking[i]);
			VikingLocation = StorVikingReference->GetActorLocation();
			RadiusToStorViking = sqrt(pow((VikingLocation.X - NewLocation.X), 2) + pow((VikingLocation.Y - NewLocation.Y), 2));
			if (RadiusToStorViking < ScareRadius)
			{
				CurrentScareOMeter = CurrentScareOMeter + ScareValue;
			}
		}
	}
}

// Finds all instances of Coins and Candy, then counts them
void ALiv::FindObjects()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), FoundCoins);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACandy::StaticClass(), FoundCandy);
	NumberOfCoins = FoundCoins.Num();
	NumberOfCandy = FoundCandy.Num();
	// If any candy is found, set one to CandyReference
	if (NumberOfCandy > 0)
	{
		for (int i = 0; i <= NumberOfCandy; i++)
		{
			CandyReference = Cast<ACandy>(FoundCandy[i]);
			CandyExist = true;
			break;
		}
	}
	// If any coin is found, set one to CoinReference
	if (NumberOfCoins > 0)
	{
		for (int i = 0; i <= NumberOfCoins; i++)
		{
			CoinReference = Cast<ACoin>(FoundCoins[i]);
			CoinExist = true;
			break;
		}
	}
	if (NumberOfCoins == 0)
	{
		CoinExist = false;
	}
	if (NumberOfCandy == 0)
	{
		CandyExist = false;
	}
}

void ALiv::RotateToCandy()
{
	FVector CandyLocation = CandyReference->GetActorLocation();
	if (CandyExist == true)
	{
		FVector TempLocation = FVector(CandyLocation.X, CandyLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.0f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
}

void ALiv::RotateToCoin()
{
	FVector CoinLocation = CoinReference->GetActorLocation();
	if (CoinExist == true)
	{
		FVector TempLocation = FVector(CoinLocation.X, CoinLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
}

void ALiv::RotateToMarve()
{
	FVector MarveLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (GetWorld())
	{
		FVector TempLocation = FVector(MarveLocation.X, MarveLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Normalize();
		NewDirection.Z = 0.f;
		SetActorRotation(NewDirection.Rotation());
	}
}

//Checks to see if there is overlapping between Liv and other actors
void ALiv::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ACandy::StaticClass()))
	{
		Cast<ACandy>(OtherActor)->Destroy();
		UE_LOG(LogTemp, Error, TEXT("Liv picked up a candy"));
		CandyExist = false;
		pickingStuff = true;
	}

	if (OtherActor->IsA(ACoin::StaticClass()))
	{
		Cast<ACoin>(OtherActor)->Destroy();
		Cast<AMarve>(GetWorld()->GetFirstPlayerController()->GetPawn())->IncreaseCoin();
		UE_LOG(LogTemp, Error, TEXT("Liv picked up a coin"));
		CoinExist = false;
		pickingStuff = true;
	}
}