// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coin.h"
#include "Liv.generated.h"

UCLASS()
class DEFENDERTROLL_API ALiv : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALiv();

	// Defines visible properties for Liv
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	// Defines direction for Vikings
	FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void RotateToCoin();

	ACoin* CoinReference;

	// Del av Bevegelses funksjon som er kommentert ut
	// TArray<AActor*> FoundActors;
private:
	UPROPERTY(EditAnywhere)
		float Speed = 150.f;
};