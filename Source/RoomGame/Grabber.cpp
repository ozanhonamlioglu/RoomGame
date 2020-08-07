// Copyright by cypgames 2020


#include "Grabber.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporter for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT mPlayerViewPointLocation,
		OUT mPlayerViewPointRotation
	);

	// log for debugging
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"), *mPlayerViewPointLocation.ToString(), *mPlayerViewPointRotation.ToString());

	// Draw a red trace in the world to visualise
	mLineTraceEnd = mPlayerViewPointLocation + mPlayerViewPointRotation.Vector() * mReach;
	DrawDebugLine(
		GetWorld(),
		mPlayerViewPointLocation,
		mLineTraceEnd,
		FColor(255, 0, 0, 1),
		false,
		0.f,
		0.f,
		10.f
	);

	// setup query params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	// Line trace (AKA ray tracing)
	GetWorld()->LineTraceSingleByObjectType(
		OUT mHit,
		mPlayerViewPointLocation,
		mLineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	// log what hits
	AActor* ActorHit = mHit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()))
	}

}

