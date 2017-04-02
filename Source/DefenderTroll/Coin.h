// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class DEFENDERTROLL_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void ReportPosition();

	/**The collision shape of the coin*/
	UPROPERTY(EditAnywhere)
		USphereComponent* CollisionBox = nullptr;

	static TArray<AActor*> NumberOfCoins;
	
};
