// Copyright by cypgames 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenMiddleDoors.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMGAME_API UOpenMiddleDoors : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenMiddleDoors();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UInputComponent *InputComponent = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *mTriggerVolume;
		
	// METHODS
	void SetupInputs(void);
	void OpenDoor(void);
};
