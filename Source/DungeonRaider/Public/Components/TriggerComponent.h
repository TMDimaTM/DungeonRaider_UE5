// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UFUNCTION(BlueprintCallable)
	void SetMoverComponent(UMoverComponent* NewMoverComponent);

private:

	UMoverComponent* MoverComponent;

	// Collision detection
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& HitResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};