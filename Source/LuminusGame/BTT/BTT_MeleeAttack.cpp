// Fill out your copyright notice in the Description page of Project Settings.

#include "BTT_MeleeAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UBTT_MeleeAttack::UBTT_MeleeAttack()
{
	// Task�� �̸��� �����մϴ�. ����� �� �����մϴ�.
	NodeName = "Melee Attack";
}

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    // AI ��Ʈ�ѷ� ��������
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // ���� ���� Pawn(ĳ����) ��������
    ACharacter* AICharacter = Cast<ACharacter>(AIController->GetPawn());
    if (AICharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // �÷��̾� ĳ���� �������� (���÷� ù ��° �÷��̾� ��Ʈ�ѷ� ���)
    ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    // AI�� �÷��̾� ������ �Ÿ� ���
    float DistanceToPlayer = FVector::Dist(AICharacter->GetActorLocation(), PlayerCharacter->GetActorLocation());

    // ���� ���� ���� ���� �ִ��� Ȯ�� (��: 200 ����)
    if (DistanceToPlayer <= 200.0f)
    {
        // ���� ���� �ִϸ��̼� ���
        AICharacter->PlayAnimMontage(MeleeAttackMontage);

        // �÷��̾�� ������ ����
        UGameplayStatics::ApplyDamage(PlayerCharacter, 10.0f, AIController, AICharacter, nullptr);

        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}
