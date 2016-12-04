// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	///get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	//if physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{

		//move the object that were holding each frame
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Pressed"));

	///LINE TRACE and see if we reach any actor with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	///if we hit something then attach a physics handle
	if (ActorHit)
	{
		//attach physics handle
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true); //true = allow rotation
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Key Released"));

	//released physics handle
	PhysicsHandle->ReleaseComponent();
}

//look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{
	///Find attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		//physics hand is found
		UE_LOG(LogTemp, Warning, TEXT("Physics handle found!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing physics handle component"), *GetOwner()->GetName());
	}
}

//look for attached input component on appear at runtime
void UGrabber::SetupInputComponent()
{
	///Find attached Input Component that only appear at runtime
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		///physics hand is found
		UE_LOG(LogTemp, Warning, TEXT("Input Component found!"));

		///bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing Input Component"), *GetOwner()->GetName());
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	///setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Line Trace aka (Ray-cast) out to reach distance.
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	///See what we hit.
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit %s "), *(ActorHit->GetName()));
	}

	return Hit;
}
