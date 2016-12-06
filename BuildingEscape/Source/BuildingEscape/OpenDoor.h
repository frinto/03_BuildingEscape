// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

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
	void CloseDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BluePrintAssignable)
		FOnOpenRequest OnOpenRequest;

	float GetOpenDoorAngle();

	float GetCloseDoorAngle();

private:

	UPROPERTY(EditAnywhere)
		float OpenDoorAngle = 90.0F;

	UPROPERTY(EditAnywhere)
		float CloseDoorAngle = 0.0F;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0F;

	float LastDoorOpenTime;

	// the owning door
	AActor* Owner = nullptr;

	//returns total mass in kg
	float GetTotalMassOfActorsOnPlate();
};
