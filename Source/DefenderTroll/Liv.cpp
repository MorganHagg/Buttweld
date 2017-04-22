// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Liv.h"
#include "coin.h"
#include "candy.h"
#include "StorViking.h"
#include "LitenViking.h"

//#include "EngineUtils.h"
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
}


// Called every frame
void ALiv::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindObjects();
	FVector LivDestination;
	FVector NewLocation = GetActorLocation();
	FVector MarveLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	CheckForViking();
	if (CurrentScareOMeter > 0 /*&& ( Time since last scared)*/)
	{
		CurrentScareOMeter = CurrentScareOMeter - CalmDown;
	}

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
			if (((RadiusToMarve - StandStillMargine) < MinimumRadius) && ((RadiusToMarve + StandStillMargine) > MinimumRadius) && ((!CandyExist) && (!CandyExist)))
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
	if (RadiusToMarve < MinimumRadius && ((!CandyExist) && (!CandyExist)))
	{
		MoveDirection = GetActorLocation() - LivDestination;
	}
	else
	{
		MoveDirection = LivDestination - GetActorLocation();
	}

	MoveDirection.Z = 0.0f;
	MoveDirection.Normalize();
}

void ALiv::CheckForViking()
{
	int VikingMultiplier = 0;
	ALitenViking* LitenVikingReference = nullptr;
	AStorViking* StorVikingReference = nullptr;
	FVector VikingLocation;
	FVector NewLocation;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALitenViking::StaticClass(), FoundLitenViking);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorViking::StaticClass(), FoundStorViking);
	NumberOfLitenViking = FoundLitenViking.Num() - 1;
	NumberOfStorViking = FoundStorViking.Num() - 1;
	//UE_LOG(LogTemp, Error, TEXT("Liv counts Liten vikings: %d"), this->NumberOfLitenViking);
	//UE_LOG(LogTemp, Error, TEXT("Liv counts Stor vikings: %d"), this->NumberOfStorViking);

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
				VikingMultiplier++;
				CurrentScareOMeter = CurrentScareOMeter + ScareValue;
				//UE_LOG(LogTemp, Error, TEXT("Liv is being scared by LitenViking. The scare-level is now: %d"), this->CurrentScareOMeter);
			}
		}
	}
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
				//UE_LOG(LogTemp, Error, TEXT("Liv is being scared by StorViking. The scare-level is now: %d"), this->CurrentScareOMeter);
			}
		}
	}
	UE_LOG(LogTemp, Error, TEXT("The scare-level is now: %d"), this->CurrentScareOMeter);
}



// Finds all instances of Coins and Candy
void ALiv::FindObjects()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), FoundCoins);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACandy::StaticClass(), FoundCandy);
	NumberOfCoins = FoundCoins.Num();
	NumberOfCandy = FoundCandy.Num();
	if (NumberOfCandy > 0)
	{
		for (int i = 0; i <= NumberOfCandy; i++)
		{
			CandyReference = Cast<ACandy>(FoundCandy[i]);
			CandyExist = true;
			break;
		}
	}
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
	}

	if (OtherActor->IsA(ACoin::StaticClass()))
	{
		Cast<ACoin>(OtherActor)->Destroy();
		UE_LOG(LogTemp, Error, TEXT("Liv picked up a coin"));
		CoinExist = false;
	}

	//if (OtherActor->IsA(ALitenViking::StaticClass()))
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Liv is being scared by LitenViking. The scare-level is now: %d"), this->ScareOMeter);
	//	
	//}
}