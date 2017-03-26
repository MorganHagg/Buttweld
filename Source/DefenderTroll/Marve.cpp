// Fill out your copyright notice in the Description page of Project Settings.

#include "DefenderTroll.h"
#include "Marve.h"
#include "Rock.h"
#include "LitenViking.h"
#include "Coin.h"


// Sets default values
AMarve::AMarve()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set the pawn to be controlled by player 1
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//// Defines the hitbox of Marve
	RootComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MySphere"));

	// Defines the visible component of the hitbox
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);


	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	// TODO: Lag en UPORPERTY som tar in materialet
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'Game/Content/Materials/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void AMarve::BeginPlay()
{
	Super::BeginPlay();
	// Sets the cameraview to CameraOne (Camera above the map)
	GetWorld()->GetFirstPlayerController()->SetViewTarget(CameraOne);

	// Show windows-cursor ingame
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;

	UWorld* World = GetWorld();
	
	CoinAmmount = 0;


	///Setter opp kollisjonstesting
	CollisionBox = this->FindComponentByClass<UBoxComponent>();
	//CollisionBox->bGenerateOverlapEvents = true;

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMarve::OnOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CollisionBox not found!"));
	}

}

// Called every frame
void AMarve::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	RotateWithMouse();
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
		//UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 00.f);
		FVector NewDirection;
		//if (CursorMesh)
		//{
		//	CursorMesh->SetWorldLocation(TempLocation);
		//}
		//else
		//{
		//	//UE_LOG(LogTemp, Warning, TEXT("Cursor Mesh not found"));	
		//}
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


}

void AMarve::Throw()
{
	UWorld* World = GetWorld();

	///Spawn one bullet if we have ammo
	// Todo: Add "ammo"
	if (World)
	{
		GetWorld()->SpawnActor<ARock>(Rock_BP, GetActorLocation() + GetActorForwardVector() * 100.f, GetActorRotation());
		//Ammo--;
	}
}

void AMarve::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f)*400.0f;
}

void AMarve::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f)*400.0f;
}

void AMarve::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(ALitenViking::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Died")) Died = true;
		this->SetActorHiddenInGame(true);
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	//if (OtherActor->IsA(ACoin::StaticClass()))
	//{
	//	OtherActor->Destroy();
	//	CoinAmmount++;
	//}


	// TODO: Make "rock-ammo" with the code under
	//if (OtherActor->IsA(AClip::StaticClass()))
	//{
	//	Ammo = AmmoInClip;
	//	UE_LOG(LogTemp, Warning, TEXT("Player Picked Up Clip"))
	//		OtherActor->Destroy();
	//}
}


// TODO: Determin what happens if Marve dies