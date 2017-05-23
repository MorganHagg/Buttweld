#pragma once

#include "GameFramework/Actor.h"
#include "LitenViking.h"
#include "StorViking.h"
#include "Rock.generated.h"

UCLASS()
class DEFENDERTROLL_API ARock : public AActor
{
	GENERATED_BODY()
	
public:	
	ARock();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

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
	
	// Holds the vector between Marves position and the mouse cursors position at the time of a rock-throw
	FVector RockDirection;

	UPROPERTY(EditAnywhere)
		float ThrowDistance = 800.0f;

	float DistanceTraveled;
};
