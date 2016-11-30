// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetOpenDoorAngle();

private:

	UPROPERTY(EditAnywhere)
		float OpenDoorAngle = 90.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	AActor* ActorThatOpensDoor; //pawn inherits from actor you can use APawn to be very specific
								//pawn is a actor.
};
