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

    // ExecuteTask �Լ��� �½�ũ�� ����� �� ȣ��˴ϴ�.
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    UFUNCTION()
    void FinishedAttacking();

protected:
    // ������ ���� �� ���ε��� �Լ�
    void BindOnAttackEndEvent(class ABaseEnemy* EnemyBase);

    // Behavior Tree ������Ʈ�� ����
    UBehaviorTreeComponent* OwnerCompRef;
};
