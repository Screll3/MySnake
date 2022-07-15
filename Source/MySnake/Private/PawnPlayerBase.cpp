// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnPlayerBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"

// Sets default values
APawnPlayerBase::APawnPlayerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;

}

// Called when the game starts or when spawned
void APawnPlayerBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-45, 0, 0));
	CreateSnakeActor();
	
}

// Called every frame
void APawnPlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnPlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("UP", this, &APawnPlayerBase::HandlePlayerYInput);
	PlayerInputComponent->BindAxis("LEFT", this, &APawnPlayerBase::HandlePlayerXInput);
}

void APawnPlayerBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
}

void APawnPlayerBase::HandlePlayerYInput(float Value)
{
	if (IsValid(SnakeActor))
	{
		if (Value > 0 && SnakeActor->LastMovementDirection!=EMovementDirection::DOWN)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::UP;
		}
		else if (Value < 0 && SnakeActor->LastMovementDirection != EMovementDirection::UP)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::DOWN;
		}
	}
}

void APawnPlayerBase::HandlePlayerXInput(float Value)
{
	if (IsValid(SnakeActor))
	{
		if (Value > 0 && SnakeActor->LastMovementDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::LEFT;
		}
		else if (Value < 0 && SnakeActor->LastMovementDirection != EMovementDirection::LEFT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::RIGHT;
		}
	}
}

