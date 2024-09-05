// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_MeleeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
	// Task의 이름을 설정합니다. 디버깅 시 유용합니다.
	NodeName = "Melee Attack";
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // AI 컨트롤러 가져오기
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // 제어 중인 Pawn(캐릭터) 가져오기
    ACharacter* AICharacter = Cast<ACharacter>(AIController->GetPawn());
    if (AICharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // 플레이어 캐릭터 가져오기 (예시로 첫 번째 플레이어 컨트롤러 사용)
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // AI와 플레이어 사이의 거리 계산
    float DistanceToPlayer = FVector::Dist(AICharacter->GetActorLocation(), PlayerCharacter->GetActorLocation());

    // 근접 공격 범위 내에 있는지 확인 (예: 200 유닛)
    if (DistanceToPlayer <= 200.0f)
    {
        // 근접 공격 애니메이션 재생
        AICharacter->PlayAnimMontage(MeleeAttackMontage);

        // 플레이어에게 데미지 적용
        UGameplayStatics::ApplyDamage(PlayerCharacter, 10.0f, AIController, AICharacter, nullptr);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
