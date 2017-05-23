#include "DefenderTroll.h"
#include "Rock.h"

ARock::ARock()
{
	PrimaryActorTick.bCanEverTick = true;

	// Creates hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));

	// Creates visible component of Rocks
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

void ARock::BeginPlay()
{
	Super::BeginPlay();

	// Sets the collisionbox to the rootcomponent
	CollisionBox = this->FindComponentByClass<USphereComponent>();

	// Checks if rock has collided with Enemy
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARock::OnOverlap);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Collider"));
	}

	// Calculates the direction Marve is facing
	FHitResult Hit;
	FVector CursorLocation;
	bool HitResult = false;
	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);
	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		if (CursorToWorld)
		{
			CursorToWorld->SetWorldLocation(Hit.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
		CursorLocation = Hit.Location;
		RockDirection = FVector(CursorLocation.X, CursorLocation.Y, 00.f);
	}
}

// Defines rock Movement
void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);
	DistanceTraveled += Speed * DeltaTime;

	// Destorys the rock if it travels too far
	if (DistanceTraveled >= ThrowDistance)
	{
		Destroy();
	}
}

//Checks to see if there is overlapping between rock and viking
void ARock::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ALitenViking::StaticClass()))
	{
		Cast<ALitenViking>(OtherActor)->HitByRock();
		this->Destroy();		
	}
	if (OtherActor->IsA(AStorViking::StaticClass()))
	{
		Cast<AStorViking>(OtherActor)->HitByRock();
		this->Destroy();
	}
}