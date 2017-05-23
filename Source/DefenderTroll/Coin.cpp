#include "DefenderTroll.h"
#include "Coin.h"


// Sets default values
ACoin::ACoin()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<USphereComponent>(TEXT("CoinSphere"));
	RootComponent = CollisionBox;
	CollisionBox->bGenerateOverlapEvents = true;
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Rotates the coin
	AddActorLocalRotation(FRotator(0.0f, RotationSpeed, 0.0f)*DeltaTime);
}