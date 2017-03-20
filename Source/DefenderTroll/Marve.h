// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Marve.generated.h"

UCLASS()
class DEFENDERTROLL_API AMarve : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMarve();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Throw();

	int CoinAmmount;

	// Rotates Marve towards cursor rotation
	virtual void RotateWithMouse();

	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
		AActor* CameraOne = nullptr;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ARock> Rock_BP;

	UPROPERTY(EditAnywhere)
		float YawSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		USceneComponent* CursorMesh = nullptr;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	bool Died = false;

	UShapeComponent* CollisionBox = nullptr;



};