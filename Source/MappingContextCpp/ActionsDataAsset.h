// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "ActionsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MAPPINGCONTEXTCPP_API UActionsDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* MoveForward;
};
