// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveAlongPatrolRoute.generated.h"
/**
 * 
 */
UCLASS()
class LUMINUSGAME_API UBTT_MoveAlongPatrolRoute : public UBTTaskNode
{
	GENERATED_BODY()

public:
    UBTT_MoveAlongPatrolRoute();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    // GetPatrolRoute 인터페이스 함수 호출
    bool GetPatrolRoute(AActor* ControlledPawn, TArray<AActor*>& OutPatrolPoints) const;

    // IncrementPatrolRoute 호출
    void IncrementPatrolRoute(AActor* ControlledPawn);
};
