// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandleComponent != nullptr && PhysicsHandleComponent->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetForwardVector() * HoldDistance + GetComponentLocation();
		FRotator TargetRotation = GetComponentRotation();

		PhysicsHandleComponent->SetTargetLocationAndRotation(TargetLocation, TargetRotation);
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult;
	bool bCanGrab = TryToGrab(HitResult);

	if (bCanGrab && PhysicsHandleComponent != nullptr)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();

		HitComponent->WakeAllRigidBodies();
		PhysicsHandleComponent->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitResult.ImpactPoint, GetComponentRotation());
	}
}

void UGrabber::UnGrab()
{
	if (PhysicsHandleComponent != nullptr && PhysicsHandleComponent->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandleComponent->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandleComponent->ReleaseComponent();
	}
}

bool UGrabber::TryToGrab(FHitResult& OutHitResult)
{
	FVector StartLocation = GetComponentLocation();
	FVector EndLocation = GetForwardVector() * MaxGrabDistance + StartLocation;
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, SphereShape);
}