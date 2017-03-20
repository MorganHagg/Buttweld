// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LitenViking.generated.h"

UCLASS()
class DEFENDERTROLL_API ALitenViking : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALitenViking();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Defines visible properties for Liten Viking
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;
	
	// Defines direction for Vikings
	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	virtual void RotateToMarve();

private:
	// Defines the movement speed of Vikings
	UPROPERTY(EditAnywhere)
		float Speed = 150.f;

};