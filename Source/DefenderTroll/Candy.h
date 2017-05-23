#pragma once

#include "GameFramework/Actor.h"
#include "Candy.generated.h"

UCLASS()
class DEFENDERTROLL_API ACandy : public AActor
{
	GENERATED_BODY()
	
public:	
	ACandy();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UDecalComponent* CursorToWorld;

	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox = nullptr;

	// Defines throw speed
	UPROPERTY(EditAnywhere)
		float Speed = 400.f;

	FVector CandyDestination;

	float ThrowDistance;
	float DistanceTraveled;

	// Sets the speed of which the candy rotates
	UPROPERTY(EditAnywhere)
		float RotationSpeed = 50.0f;
};
