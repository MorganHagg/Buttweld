#pragma once

#include "GameFramework/Actor.h"
#include "Coin.generated.h"

UCLASS()
class DEFENDERTROLL_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	ACoin();

	virtual void BeginPlay() override;	
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		USphereComponent* CollisionBox = nullptr;

	// Sets the speed of which the coin rotates
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 50.0f;	
};
