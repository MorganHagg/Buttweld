// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Melee.h"
#include "LitenViking.h"
#include "StorViking.h"


// Sets default values
AMelee::AMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBox"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMelee::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Attack is inbound"));
	CollisionBox = this->FindComponentByClass<UBoxComponent>();

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMelee::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}
}

// Called every frame
void AMelee::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * Speed * DeltaTime;
	SetActorLocation(NewLocation);

	DistanceTraveled += Speed * DeltaTime;

	if (DistanceTraveled >= MeleeRange)
	{
		this->Destroy();
	}
}

//Checks to see if there is overlapping between HitBox and Enemy
void AMelee::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ALitenViking::StaticClass()))
	{
		Cast<ALitenViking>(OtherActor)->HitByMelee();
		Destroy();
	}
	if (OtherActor->IsA(AStorViking::StaticClass()))
	{
		Cast<AStorViking>(OtherActor)->HitByMelee();
		Destroy();
	}
}