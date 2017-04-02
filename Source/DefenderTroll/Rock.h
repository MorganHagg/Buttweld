// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Rock.generated.h"

UCLASS()
class DEFENDERTROLL_API ARock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARock();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Make editable anywhere
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	// Defines throw speed
	UPROPERTY(EditAnywhere)
		float Speed = 400.f;

	// Initialising for collision and overlap
	UShapeComponent* CollisionBox = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor *OtherActor, UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	FVector RockDestination;
	float ThrowDistance;
	float DistanceTraveled;
};
