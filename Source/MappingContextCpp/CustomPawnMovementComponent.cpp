// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPawnMovementComponent.h"

void UCustomPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Display, TEXT("Component Tick()"));

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Component Tick() After Check"));

	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 1500.0f;
	UE_LOG(LogTemp, Display, TEXT("DesiredMovementThisFrame = %s"), *DesiredMovementThisFrame.ToString());
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		UE_LOG(LogTemp, Display, TEXT("IsNearlyZero"));
		
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.0f - Hit.Time, Hit.Normal, Hit);
		}
	}
}