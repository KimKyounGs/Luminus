#include "AIC_Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"

AAIC_Enemy_Base::AAIC_Enemy_Base()
{
    // ������ ������Ʈ ����
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // �����忡�� ����� Ű �̸� �ʱ�ȭ
    PawnKeyName = "AttackTarget";
}

void AAIC_Enemy_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn && BehaviorTreeAsset)
    {
        // �����带 �ʱ�ȭ�ϰ� �ൿ Ʈ���� ����
        if (UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComponent))
        {
            // Pawn ��ü�� �����忡 ����
            BlackboardComponent->SetValueAsObject(PawnKeyName, InPawn);

            // �ൿ Ʈ���� ����
            RunBehaviorTree(BehaviorTreeAsset);
        }
    }
}
