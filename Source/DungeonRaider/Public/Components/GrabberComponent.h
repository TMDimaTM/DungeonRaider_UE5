// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float MaxGrabDistance;

	UPROPERTY(EditAnywhere)
	float GrabRadius;

	UPROPERTY(EditAnywhere)
	float HoldDistance;

	class UPhysicsHandleComponent* PhysicsHandleComponent;

	bool TryToGrab(FHitResult& OutHitResult);

public:

	void Grab();
	void UnGrab();
};