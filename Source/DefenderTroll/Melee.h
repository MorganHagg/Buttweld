// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Melee.generated.h"

UCLASS()
class DEFENDERTROLL_API AMelee : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMelee();

	// Initialising for collision and overlap

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	UShapeComponent* CollisionBox = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor *OtherActor, UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

private:

	UPROPERTY(EditAnywhere)
		float MeleeRange = 100.0f;

	FVector CurrentPosition;
	FVector FrontOfMarve;
	FRotator CurrentRotation;
	FVector CurrentVector;
	
};
