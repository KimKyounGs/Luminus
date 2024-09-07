#include "AIC_Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"

AAIC_Enemy_Base::AAIC_Enemy_Base()
{
    // 블랙보드 컴포넌트 생성
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // 블랙보드에서 사용할 키 이름 초기화
    PawnKeyName = "AttackTarget";
}

void AAIC_Enemy_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn && BehaviorTreeAsset)
    {
        // 블랙보드를 초기화하고 행동 트리를 실행
        if (UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComponent))
        {
            // Pawn 객체를 블랙보드에 저장
            BlackboardComponent->SetValueAsObject(PawnKeyName, InPawn);

            // 행동 트리를 실행
            RunBehaviorTree(BehaviorTreeAsset);
        }
    }
}
