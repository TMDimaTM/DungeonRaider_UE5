// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
	StartLocation = Owner->GetActorLocation();
	CurrentLocation = StartLocation;
	TargetLocation = MoveOffset.GetSafeNormal() * MoveOffset + StartLocation;

	MoveSpeed = FVector::Distance(StartLocation, TargetLocation) / MoveTime;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bShouldMove)
	{
		CurrentLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
		Owner->SetActorLocation(CurrentLocation);
	}
}