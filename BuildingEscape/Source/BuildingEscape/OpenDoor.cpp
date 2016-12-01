// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, GetOpenDoorAngle(), 0.f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, GetCloseDoorAngle(), 0.f));
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//get the owner of the door
	Owner = GetOwner();

	//the pawn / player that will open the door
	ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll trigger volume every frame
	//if ActorThatOpensDoor is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//check if time to close the door
	if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

float UOpenDoor::GetOpenDoorAngle()
{
	return OpenDoorAngle;
}

float UOpenDoor::GetCloseDoorAngle()
{
	return CloseDoorAngle;
}

