// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	Idle       UMETA(DisplayName = "Idle"),
	Walking    UMETA(DisplayName = "Walking"),
	Jogging    UMETA(DisplayName = "Jogging"),
	Sprinting  UMETA(DisplayName = "Sprinting")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LUMINUSGAME_API IEnemyInterface
{
	GENERATED_BODY()

public:
	// 순찰 경로를 반환하는 함수 선언
	virtual TArray<FVector> GetPatrolRoute() const = 0;

	// 인터페이스 함수 선언
	virtual float SetMovementSpeed(EMovementStatus Speed) = 0;
};
