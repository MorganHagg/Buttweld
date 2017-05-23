#include "DefenderTroll.h"
#include "Liv.h"
#include "StorViking.h"

AStorViking::AStorViking()
{
	// Creates hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	// Visible component
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void AStorViking::BeginPlay()
{
	Super::BeginPlay();
	Cast<AMarve>(GetWorld()->GetFirstPlayerController()->GetPawn())->IncreaseViking();
	isDead = false;
}

void AStorViking::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Finds all instances of Liv, and sets the "LivReference" to the first ([0]) actor found
	TArray<AActor*> FoundActors;
	ALiv* LivReference = nullptr;
	if (LivReference == nullptr)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALiv::StaticClass(), FoundActors);
		LivReference = Cast<ALiv>(FoundActors[0]);
	}
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
}

void AStorViking::RotateToLiv(AActor* LivReference)
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

void AStorViking::HitByRock()
{
	if (Health > 0)
	{
		Health = Health - DamageByRock;
	}
	if (Health < 1 && (!isDead))
	{
		Death();
	}
}

void AStorViking::Death()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Coin spawned"));
	GetWorld()->SpawnActor<ACoin>(Coin_BP, Location, FRotator::ZeroRotator);
	isDead = true;
	Cast<AMarve>(GetWorld()->GetFirstPlayerController()->GetPawn())->DecreaseViking();
}

void AStorViking::GameWon()
{
	this->Destroy();
}
