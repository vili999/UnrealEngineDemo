// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "ShipMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FLYINGEXAMPLE_API UShipMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	UShipMovementComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveForward(float AxisValue);
	void SlideRight(float AxisValue);
	void SlideUp(float AxisValue);
	void Turn(float AxisValue);
	void LookUp(float AxisValue);

	UPROPERTY(EditAnywhere, Category = ShipMovement, BlueprintReadOnly)
	float  MaxAcceleration;

	UPROPERTY(EditAnywhere, Category = ShipMovement, BlueprintReadOnly)
	float TurnSpeed;

protected:
	FVector Acceleration;
	float CurrentPitch;
	float CurrentYaw;
	float CurrentRoll;
};
