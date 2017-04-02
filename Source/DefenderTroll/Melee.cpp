// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Melee.h"
#include "LitenViking.h"


// Sets default values
AMelee::AMelee()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Defines hitbox
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MySphere"));

	// Defines visible component of Rocks
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMelee::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Attack is inbound"));
	CollisionBox = this->FindComponentByClass<USphereComponent>();
	// Checks if Melee has collided with Enemy
	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMelee::OnOverlap);
	}

}

// Called every frame
void AMelee::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	CurrentPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	CurrentRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
	CurrentVector = CurrentRotation.Vector();
	
	FrontOfMarve = CurrentPosition + (CurrentVector)* MeleeRange;

	SetActorLocation(FrontOfMarve);
	SetActorRotation(CurrentRotation);
}

//Checks to see if there is overlapping between HitBox and Enemy
void AMelee::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor,
	UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ALitenViking::StaticClass()))
	{
		Cast<ALitenViking>(OtherActor)->HitByRock();
		UE_LOG(LogTemp, Warning, TEXT("Hitting viking"));
	}
}