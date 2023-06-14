// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CustomPawnMovementComponent.h"
#include "ActionsDataAsset.h"
#include "MovingPawn.generated.h"

UCLASS()
class MAPPINGCONTEXTCPP_API AMovingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingPawn();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
	void MoveForward(const FInputActionValue&);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mapping Context")
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere)
	UActionsDataAsset* InputActions;
	
	UPROPERTY()
	UCustomPawnMovementComponent* MovementComponent;

};
