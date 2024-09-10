#include "AIC_Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AAIC_Enemy_Base::AAIC_Enemy_Base()
{
    // 블랙보드 컴포넌트 생성
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // 블랙보드에서 사용할 키 설정
    AttackTargetKeyName = "AttackTarget";
}

void AAIC_Enemy_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // 소유된 Pawn이 있고, 행동 트리 자산이 설정되어 있으면
    if (InPawn && BehaviorTreeAsset)
    {
        // 0.2초 딜레이 후 행동 트리를 실행하는 함수 호출
        GetWorld()->GetTimerManager().SetTimerForNextTick([this, InPawn]()
        {
            StartBehaviorAfterDelay(InPawn);
        });
    }
}

void AAIC_Enemy_Base::StartBehaviorAfterDelay(APawn* InPawn)
{
    // 행동 트리 실행 및 블랙보드 초기화
    if (UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComponent))
    {
        InitializeBlackboard(InPawn);

        // 행동 트리 실행
        RunBehaviorTree(BehaviorTreeAsset);
    }
}

void AAIC_Enemy_Base::InitializeBlackboard(APawn* InPawn)
{
    if (BlackboardComponent)
    {
        // 플레이어 캐릭터를 블랙보드에 저장
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        APawn* PlayerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;

        if (PlayerPawn)
        {
            BlackboardComponent->SetValueAsObject(AttackTargetKeyName, PlayerPawn);
        }
    }
}