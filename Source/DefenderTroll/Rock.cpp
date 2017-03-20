// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Rock.h"
#include "LitenViking.h"


// Sets default values
ARock::ARock()
{
	// Set Bullets to call Tick function every frame
	PrimaryActorTick.bCanEverTick = true;

	// Defines hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));

	// Defines visible component of Bullets
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts
void ARock::BeginPlay()
{
	Super::BeginPlay();

	//Info to Output Log
	UE_LOG(LogTemp, Warning, TEXT("Spawned Rock"));

	//Checks if there is overlap
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
		UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());
		RockDestination = FVector(CursorLocation.X, CursorLocation.Y, 00.f);
	}

	FVector CurrentLocation = GetActorLocation();

	ThrowDistance = sqrt(pow((CursorLocation.X - CurrentLocation.X),2) + pow((CursorLocation.Y - CurrentLocation.Y),2));
	UE_LOG(LogTemp, Error, TEXT("Throw distance %f"), ThrowDistance);

}



// Defines Bullet Movement
void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);

	
	DistanceTraveled += Speed * DeltaTime;

	if (DistanceTraveled >= ThrowDistance)
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Rock destroyed"));
	}


}

//Checks to see if there is overlapping between Bullet and Alien
void ARock::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ALitenViking::StaticClass()))
	{
		OtherActor->Destroy();
		Destroy();
	}

}