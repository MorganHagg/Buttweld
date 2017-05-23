#include "DefenderTroll.h"
#include "Ammo.h"

AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AmmoSphere"));
	RootSphere->SetSphereRadius(SphereRadius);
	RootComponent = RootSphere;
	RootSphere->bGenerateOverlapEvents = true;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();
}

void AAmmo::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}