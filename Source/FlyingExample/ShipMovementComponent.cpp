// Fill out your copyright notice in the Description page of Project Settings.

#include "ShipMovementComponent.h"

UShipMovementComponent::UShipMovementComponent()
{
	MaxAcceleration = 10000.0f;
	TurnSpeed = 50.0f;
	Acceleration = FVector::ZeroVector;
	CurrentPitch = 0.0f;
	CurrentYaw = 0.0f;
	CurrentRoll = 0.0f;
}

void UShipMovementComponent::MoveForward(float AxisValue)
{
	if (PawnOwner && UpdatedComponent == PawnOwner->GetRootComponent())
	{
		AddInputVector(PawnOwner->GetActorForwardVector() * AxisValue);
	}
}

void UShipMovementComponent::SlideRight(float AxisValue)
{
	if (PawnOwner && UpdatedComponent == PawnOwner->GetRootComponent())
	{
		AddInputVector(PawnOwner->GetActorRightVector() * AxisValue);
	}
}

void UShipMovementComponent::SlideUp(float AxisValue)
{
	if (PawnOwner && UpdatedComponent == PawnOwner->GetRootComponent())
	{
		AddInputVector(PawnOwner->GetActorUpVector() * AxisValue);
	}
}

void UShipMovementComponent::Turn(float AxisValue)
{
	float deltaTime = GetWorld()->GetDeltaSeconds();

	float TargetYaw = (AxisValue * TurnSpeed);

	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, deltaTime, 2.0f);

	const bool bIsTurning = FMath::Abs(AxisValue) > 0.2f;

	float interpSpeed = bIsTurning ? 20.0f : 40.0f;
	float TargetRoll = bIsTurning ? 20.0f * AxisValue : 0.0f;

	CurrentRoll = FMath::FInterpTo(CurrentRoll, TargetRoll, deltaTime, interpSpeed);
}

void UShipMovementComponent::LookUp(float AxisValue)
{
	float TargetPitch = (AxisValue * TurnSpeed * -1.0f);

	CurrentPitch = FMath::FInterpTo(CurrentPitch, TargetPitch, GetWorld()->GetDeltaSeconds(), 2.0f);
}

void UShipMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Calculate change in rotation this frame
	FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitch * DeltaTime;
	DeltaRotation.Yaw = CurrentYaw * DeltaTime;
	DeltaRotation.Roll = (CurrentRoll - CurrentRotation.Roll) * DeltaTime;

	UpdatedComponent->AddLocalRotation(DeltaRotation);
	PawnOwner->AddControllerPitchInput(DeltaRotation.Pitch);
	PawnOwner->AddControllerYawInput(DeltaRotation.Yaw);
	PawnOwner->AddControllerRollInput(DeltaRotation.Roll);

	// Get and clear the movement vector that we set using AddInputVector
	const FVector InputVector = ConsumeInputVector().GetClampedToMaxSize(1.0f);
	Acceleration += InputVector * MaxAcceleration;
	Acceleration = Acceleration.GetClampedToMaxSize(MaxAcceleration);

	//Update velocity and displacement
	Velocity += Acceleration * DeltaTime;
	FVector DesiredMovementThisFrame = Velocity * DeltaTime;

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		CurrentRotation = UpdatedComponent->GetComponentRotation();
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, CurrentRotation, true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}

	// Add some damping so ship come to a halt if there is no input 
	Acceleration *= 0.65f;
	Velocity *= 0.95f;
}