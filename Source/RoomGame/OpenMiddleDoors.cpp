// Copyright by cypgames 2020


#include "OpenMiddleDoors.h"

#define OUT

// Sets default values for this component's properties
UOpenMiddleDoors::UOpenMiddleDoors()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenMiddleDoors::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetupInputs();
}


// Called every frame
void UOpenMiddleDoors::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UOpenMiddleDoors::OpenDoor()
{

	TArray<AActor*> OverlappingActors;

	if (mTriggerVolume)
		mTriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	GetOwner()->SetActorRotation(FRotator(0.f, 180.0f, 0.f));


}

void UOpenMiddleDoors::SetupInputs(void)
{
	InputComponent = GetWorld()->GetFirstPlayerController()->FindComponentByClass<UInputComponent>(); // GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Open", IE_Pressed, this, &UOpenMiddleDoors::OpenDoor);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[-] InputComponent is missing!"))
	}
}