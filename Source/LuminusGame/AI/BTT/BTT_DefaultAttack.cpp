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
    // OwnerComp를 전역 변수로 저장하여 다른 함수에서도 접근 가능하게 설정
    OwnerCompRef = &OwnerComp;

    // AIController와 Controlled Pawn을 가져옵니다.
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

    if (!ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    // 캐릭터를 적 클래스로 캐스팅
    ABaseEnemy* EnemyBase = Cast<ABaseEnemy>(ControlledPawn);
    if (!EnemyBase)
    {
        return EBTNodeResult::Failed;
    }

    // Attack 함수를 호출하여 공격을 시작
    EnemyBase->Attack();

    // 공격이 끝날 때 바인딩될 이벤트 설정
    BindOnAttackEndEvent(EnemyBase);

    return EBTNodeResult::InProgress;  // 태스크가 진행 중임을 알림
}

void UBTT_DefaultAttack::BindOnAttackEndEvent(ABaseEnemy* EnemyBase)
{
    if (EnemyBase)
    {
        // 공격이 끝났을 때 호출될 OnAttackEnd 델리게이트 바인딩
        EnemyBase->OnAttackEnd.AddDynamic(this, &UBTT_DefaultAttack::FinishedAttacking);
    }
}

void UBTT_DefaultAttack::FinishedAttacking()
{
    // 공격이 끝났을 때 호출되는 함수
    UE_LOG(LogTemp, Warning, TEXT("Attack Finished"));

    // AI 태스크가 성공적으로 완료되었음을 알림
    FinishLatentTask(*OwnerCompRef, EBTNodeResult::Succeeded);
}
