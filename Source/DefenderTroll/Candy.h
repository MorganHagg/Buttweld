// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Candy.generated.h"

UCLASS()
class DEFENDERTROLL_API ACandy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACandy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	// Make editable anywhere
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	FVector CandyDestination;
	// Initialising for collision and overlap
	UShapeComponent* CollisionBox = nullptr;

	// Defines throw speed
	UPROPERTY(EditAnywhere)
		float Speed = 400.f;

	float ThrowDistance;
	float DistanceTraveled;
	
};
