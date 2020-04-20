// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipMovementComponent.h"
#include "Ship.generated.h"

UCLASS()
class FLYINGEXAMPLE_API AShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShip();

	virtual UShipMovementComponent* GetMovementComponent() const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	UPROPERTY(EditAnywhere, Category = Ship, BlueprintReadOnly, meta = (DisplayName = "Ship Collision"))
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = Ship, BlueprintReadOnly, meta = (DisplayName = "Ship Camera"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = Ship, BlueprintReadOnly, meta = (DisplayName = "Ship Movement"))
	UShipMovementComponent *MovementComponent;
};
