// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_DefaultAttack.generated.h"
/**
 * 
 */
UCLASS()
class LUMINUSGAME_API UBTT_DefaultAttack : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTT_DefaultAttack();

    // ExecuteTask 함수는 태스크가 실행될 때 호출됩니다.
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION()
    void FinishedAttacking();

protected:
    // 공격이 끝날 때 바인딩될 함수
    void BindOnAttackEndEvent(class ABaseEnemy* EnemyBase);

    // Behavior Tree 컴포넌트를 참조
    UBehaviorTreeComponent* OwnerCompRef;
};
