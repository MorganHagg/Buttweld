#pragma once
#include "GameFramework/Actor.h"
#include "Coin.h"
#include "Marve.h"
#include "Liv.generated.h"

class ALitenViking;
class AStorViking;

UCLASS()
class DEFENDERTROLL_API ALiv : public AActor
{
	GENERATED_BODY()

		
public:
	ALiv();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void RotateToCoin();
	void RotateToCandy();
	void RotateToMarve();
	void FindObjects();
	void CheckForViking();

	ACoin* CoinReference = nullptr;
	ACandy* CandyReference = nullptr;

	TArray<AActor*> FoundCoins;
	TArray<AActor*> FoundCandy;
	TArray<AActor*> FoundLitenViking;
	TArray<AActor*> FoundStorViking;

	bool CoinExist;
	bool CandyExist;

	int NumberOfCoins;
	int NumberOfCandy;
	int NumberOfLitenViking;
	int NumberOfStorViking;

	// Initialising for collisionbox
	UShapeComponent* CollisionBox = nullptr;

	// Defines visible properties for Liv
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

	UPROPERTY(BlueprintReadWrite)
		FVector MoveDirection = FVector(1.f, 0.f, 0.f);

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor *OtherActor, UPrimitiveComponent *OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	// Sets the max value of the scare-o-meter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ScareOMeter)
		float MaxScareOMeter = 1000.0f;

	// Reads the current value of scare-o-meter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ScareOMeter)
		float CurrentScareOMeter = 0.0f;
	
	// Sets the value the scare-o-meter drops by every frame
	UPROPERTY(EditAnywhere)
		float CalmDown = 5.0f;
	
	// Sets the value the scare-o-meter increases every frame for every viking within range
	UPROPERTY(EditAnywhere)
		float ScareValue = 10.0f;

	// Sets the minimum distance Liv will walk to Marve (cm)
	UPROPERTY(EditAnywhere)
		float MinimumRadius = 100.0f;

	// Reads the current distance from Liv to Marve (cm)
	UPROPERTY(EditAnywhere)
		float RadiusToMarve;

	// Sets the distance from Liv to Viking which triggers scare-o-meter to increase (cm)
	UPROPERTY(EditAnywhere)
		float ScareRadius = 100.0f;

	// Reads the distanace from Liv to LitenViking
	UPROPERTY(EditAnywhere)
		float RadiusToLitenViking;

	// Reads the distanace from Liv to StorViking
	UPROPERTY(EditAnywhere)
		float RadiusToStorViking;

	// Sets Livs movement speed
	UPROPERTY(EditAnywhere)
		float Speed = 150.0f;

	//Sets the error-margine to avoid stuttering due to Liv being unable to find the exact locations of destinations
	UPROPERTY(EditAnywhere)
		float StandStillMargine = 5.0f;

	UPROPERTY(BlueprintReadWrite)
		bool pickingStuff;

	bool CanWalk;
};
