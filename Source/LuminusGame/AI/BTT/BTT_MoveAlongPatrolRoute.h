// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/SplineComponent.h"  // 스플라인 컴포넌트 관련 헤더 추가
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

    // IncrementPatrolRoute 호출
    void IncrementPatrolRoute(USplineComponent* PatrolRouteSpline);
};
