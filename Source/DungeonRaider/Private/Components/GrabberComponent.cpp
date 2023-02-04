// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GrabberComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxGrabDistance = 250.0f;
	GrabRadius = 100.0f;
	HoldDistance = 150.0f;
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandleComponent != nullptr && PhysicsHandleComponent->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetForwardVector() * HoldDistance + GetComponentLocation();
		FRotator TargetRotation = GetComponentRotation();

		PhysicsHandleComponent->SetTargetLocationAndRotation(TargetLocation, TargetRotation);
	}
}

void UGrabberComponent::Grab()
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

void UGrabberComponent::UnGrab()
{
	if (PhysicsHandleComponent != nullptr && PhysicsHandleComponent->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandleComponent->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandleComponent->ReleaseComponent();
	}
}

bool UGrabberComponent::TryToGrab(FHitResult& OutHitResult) const
{
	FVector StartLocation = GetComponentLocation();
	FVector EndLocation = GetForwardVector() * MaxGrabDistance + StartLocation;
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(OutHitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel2, SphereShape);
}