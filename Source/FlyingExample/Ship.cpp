// Fill out your copyright notice in the Description page of Project Settings.

#include "Ship.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->RelativeLocation = FVector(0, 0, 0);
	CameraComponent->bUsePawnControlRotation = false;

	MovementComponent = CreateDefaultSubobject<UShipMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

UShipMovementComponent * AShip::GetMovementComponent() const
{
	return MovementComponent;
}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UShipMovementComponent::MoveForward);
	PlayerInputComponent->BindAxis("SlideRight", MovementComponent, &UShipMovementComponent::SlideRight);
	PlayerInputComponent->BindAxis("SlideUp", MovementComponent, &UShipMovementComponent::SlideUp);
	PlayerInputComponent->BindAxis("Turn", MovementComponent, &UShipMovementComponent::Turn);
	PlayerInputComponent->BindAxis("LookUp", MovementComponent, &UShipMovementComponent::LookUp);
}

