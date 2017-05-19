// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Marve.h"

// Sets default values
AMarve::AMarve()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set the pawn to be controlled by player 1
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Defines the visible component of the hitbox
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AMarve::BeginPlay()
{
	Super::BeginPlay();
	// Show windows-cursor ingame
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GameWon = false;
}

// Called every frame
void AMarve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ThrowTime += DeltaTime;

	TimeTillThrow = candyThrowDelay - ThrowTime;

	if (ThrowTime > candyThrowDelay)
	{
		bCandyEnabled = true;
	}
	else
	{
		bCandyEnabled = false;
		UE_LOG(LogTemp, Warning, TEXT("Marve can't throw candy yet. Time till throw: %f"), this->TimeTillThrow);
	}

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	RotateWithMouse();
	if (CoinCount >= WinAmmount)
	{
		GameWon = true;
	}
}

void AMarve::IncreaseViking()
{
	EnemyCount++;
}

void AMarve::DecreaseViking()
{
	EnemyCount--;
}

void AMarve::IncreaseCoin()
{
	CoinCount++;
}

void AMarve::RotateWithMouse()
{
	FHitResult Hit;
	bool HitResult = false;
	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);
	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();
		CursorToWorld->SetWorldLocation(Hit.Location);
		CursorToWorld->SetWorldRotation(CursorR);
		FVector CursorLocation = Hit.Location;
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 00.f);
		FVector NewDirection;
		NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		SetActorRotation(NewDirection.Rotation());
	}

}

// Called to bind functionality to input
void AMarve::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("Move_X", this, &AMarve::Move_XAxis);
	InputComponent->BindAxis("Move_Y", this, &AMarve::Move_YAxis);
	InputComponent->BindAction("Throw", IE_Pressed, this, &AMarve::Throw);
	InputComponent->BindAction("Candy", IE_Pressed, this, &AMarve::CandyThrow);
}

void AMarve::Throw()
{
	//Spawn one bullet if we have ammo
	if (AmmoCount > 0)
	{
		GetWorld()->SpawnActor<ARock>(Rock_BP, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
		AmmoCount--;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Marve doesn't have any rocks!"));
	}
}

void AMarve::CandyThrow()
{
	UWorld* World = GetWorld();
	if (bCandyEnabled)
	{
		GetWorld()->SpawnActor<ACandy>(Candy_BP, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
		ThrowTime -= candyThrowDelay;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Marve can't throw candy yet"))
	}
}

void AMarve::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}

void AMarve::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}
