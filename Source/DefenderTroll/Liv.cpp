// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Liv.h"
#include "Coin.h"
#include "Candy.h"
#include "Marve.h"
#include "EngineUtils.h"
#include "LitenViking.h"


// TODO Gjøre så tick har en "If (Coin eksisterer BOOL) istedenfor if(Coinreference)


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
	// Checks if rock has collided with Enemy
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALiv::OnOverlap);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Collider"));
	}
	CoinExist = false;
}


// Called every frame
void ALiv::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();

	// Finds all instances of Coins and Candy
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACoin::StaticClass(), FoundCoins);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACandy::StaticClass(), FoundCandy);
	NumberOfCoins = FoundCoins.Num();
	NumberOfCandy = FoundCandy.Num();

	if (NumberOfCoins > 0)
	{
		for (int i = 0; i <= NumberOfCoins; i++)
		{
			CoinReference = Cast<ACoin>(FoundCoins[i]);
			CoinExist = true;
			break;
		}
	}

	if (NumberOfCandy > 0)
	{
		for (int i = 0; i <= NumberOfCandy; i++)
		{
			CandyReference = Cast<ACandy>(FoundCandy[i]);
			CandyExist = true;
			break;
		}
	}

	if (NumberOfCoins == 0)
	{
		CoinExist = false;
	}

	if (NumberOfCandy == 0 )
	{
		CandyExist = false;
	}

	if (ScareOMeter > 0)
	{
		ScareOMeter = ScareOMeter - CalmDown;
	}

	if (CandyExist == true)
	{
		RotateToCandy();
		NewLocation += (MoveDirection * Speed * DeltaTime);
		SetActorLocation(NewLocation);
		MoveDirection = CandyReference->GetActorLocation() - GetActorLocation();
		MoveDirection.Normalize();
	}
	else
	{
		if (CoinExist == true)
		{
			RotateToCoin();
			NewLocation += (MoveDirection * Speed * DeltaTime);
			SetActorLocation(NewLocation);
			MoveDirection = CoinReference->GetActorLocation() - GetActorLocation();
			MoveDirection.Normalize();
		}
		else
		{
			NewLocation += (MoveDirection * Speed * DeltaTime);
			SetActorLocation(NewLocation);
			MoveDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - GetActorLocation();
			MoveDirection.Normalize();
		}
	}

	
}

void ALiv::RotateToCandy()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector CoinLocation = CandyReference->GetActorLocation();
	FHitResult Hit;
	bool HitResult = false;
	if (CandyExist == true)
	{
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(CoinLocation.X, CoinLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
	else
	{
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
}

void ALiv::RotateToCoin()
{
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector CoinLocation = CoinReference->GetActorLocation();
	FHitResult Hit;
	bool HitResult = false;
	if (CoinExist == true)
	{
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(CoinLocation.X, CoinLocation.Y, 00.f);
		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}
	else
	{
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
}

//Checks to see if there is overlapping between Liv and other actors
void ALiv::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ACandy::StaticClass()))
	{
		Cast<ACandy>(OtherActor)->Destroy();
		UE_LOG(LogTemp, Error, TEXT("Liv picked up a coin"));
		CandyExist = false;
	}

	if (OtherActor->IsA(ACoin::StaticClass()))
	{
		Cast<ACoin>(OtherActor)->Destroy();
		UE_LOG(LogTemp, Error, TEXT("Liv picked up a coin"));
		CoinExist = false;
	}

	if (OtherActor->IsA(ALitenViking::StaticClass()))
	{
		UE_LOG(LogTemp, Error, TEXT("Liv is being scared by LitenViking"));
		//ScareOMeter = ScareOMeter + ScareValue;
	}
}