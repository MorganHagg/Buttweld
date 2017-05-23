#pragma once

#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UCLASS()
class DEFENDERTROLL_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	AAmmo();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	//The collision shape of the ammo
	UPROPERTY(EditAnywhere)
		USphereComponent* RootSphere = nullptr;

	UPROPERTY(EditAnywhere)
		float SphereRadius = 40.0f;
};
