// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TriggerComponent.h"
#include "Actors/SecretKeyActor.h"
#include "Components/MoverComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::BeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::EndOverlap);
}


// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTriggerComponent::SetMoverComponent(UMoverComponent* NewMoverComponent)
{
	MoverComponent = NewMoverComponent;
}

void UTriggerComponent::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& HitResult)
{
	if (Cast<ASecretKeyActor>(OtherActor) && MoverComponent != nullptr)
	{
		MoverComponent->bShouldMove = true;
	}
}

void UTriggerComponent::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (MoverComponent != nullptr)
	{
		TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors);
		if (OverlappingActors.Num() > 0)
		{
			for (AActor* Actor : OverlappingActors)
			{
				if (Cast<ASecretKeyActor>(Actor))
				{
					return;
				}
			}
			MoverComponent->bShouldMove = false;
		}
		else
		{
			MoverComponent->bShouldMove = false;
		}
	}
}