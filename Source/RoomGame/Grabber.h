// Copyright by cypgames 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMGAME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector mPlayerViewPointLocation;
	FRotator mPlayerViewPointRotation;
	FVector mLineTraceEnd;
	FHitResult mHit;
	float mReach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandler = nullptr;
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what is reached
	void Grab();
	void Release();

	// Find attached physics component
	void FindPhysicsHandleComponent();

	// Set-Up attached input component
	void SetupInputComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReact();
	void setStateReachLineStartandEnd();
};
