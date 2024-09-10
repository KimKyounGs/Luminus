// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DefaultAttack.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "LuminusGame/AI/BaseEnemy.h" 
#include "BehaviorTree/BlackboardComponent.h"

UBTT_DefaultAttack::UBTT_DefaultAttack()
{
	NodeName = "Attack Target";
}

EBTNodeResult::Type UBTT_DefaultAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // OwnerComp�� ���� ������ �����Ͽ� �ٸ� �Լ������� ���� �����ϰ� ����
    OwnerCompRef = &OwnerComp;

    // AIController�� Controlled Pawn�� �����ɴϴ�.
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    // ĳ���͸� �� Ŭ������ ĳ����
    ABaseEnemy* EnemyBase = Cast<ABaseEnemy>(ControlledPawn);
    if (!EnemyBase)
    {
        return EBTNodeResult::Failed;
    }

    // Attack �Լ��� ȣ���Ͽ� ������ ����
    EnemyBase->Attack();

    // ������ ���� �� ���ε��� �̺�Ʈ ����
    BindOnAttackEndEvent(EnemyBase);

    return EBTNodeResult::InProgress;  // �½�ũ�� ���� ������ �˸�
}

void UBTT_DefaultAttack::BindOnAttackEndEvent(ABaseEnemy* EnemyBase)
{
    if (EnemyBase)
    {
        // ������ ������ �� ȣ��� OnAttackEnd ��������Ʈ ���ε�
        EnemyBase->OnAttackEnd.AddDynamic(this, &UBTT_DefaultAttack::FinishedAttacking);
    }
}

void UBTT_DefaultAttack::FinishedAttacking()
{
    // ������ ������ �� ȣ��Ǵ� �Լ�
    UE_LOG(LogTemp, Warning, TEXT("Attack Finished"));

    // AI �½�ũ�� ���������� �Ϸ�Ǿ����� �˸�
    FinishLatentTask(*OwnerCompRef, EBTNodeResult::Succeeded);
}
