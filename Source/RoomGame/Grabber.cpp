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


void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	// LINE TRACE and see if we reach any actors with physics body collision channel is set
	auto HitResult = GetFirstPhysicsBodyInReact();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActoHit = HitResult.GetActor();

	// if we hit something then attach a physics handle
	if (ActoHit != nullptr)
	{
		// TODO attach physics handle
		//PhysicsHandler->GrabComponentAtLocation(
		//	ComponentToGrab,
		//	NAME_None,
		//	ComponentToGrab->GetOwner()->GetActorLocation());
		PhysicsHandler->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation());
	}

}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));

	// TODO release physics handle
	PhysicsHandler->ReleaseComponent();
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandler) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component!"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component!"), *GetOwner()->GetName())
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
	if (PhysicsHandler->GrabbedComponent)
	{
		// move the object that we are holding
		UE_LOG(LogTemp, Warning, TEXT("teest"))
		PhysicsHandler->SetTargetLocation(mLineTraceEnd);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReact()
{
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

	return mHit;
}