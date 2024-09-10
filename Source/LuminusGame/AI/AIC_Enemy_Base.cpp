#include "AIC_Enemy_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AAIC_Enemy_Base::AAIC_Enemy_Base()
{
    // ������ ������Ʈ ����
    BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    // �����忡�� ����� Ű ����
    AttackTargetKeyName = "AttackTarget";
}

void AAIC_Enemy_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // ������ Pawn�� �ְ�, �ൿ Ʈ�� �ڻ��� �����Ǿ� ������
    if (InPawn && BehaviorTreeAsset)
    {
        // 0.2�� ������ �� �ൿ Ʈ���� �����ϴ� �Լ� ȣ��
        GetWorld()->GetTimerManager().SetTimerForNextTick([this, InPawn]()
        {
            StartBehaviorAfterDelay(InPawn);
        });
    }
}

void AAIC_Enemy_Base::StartBehaviorAfterDelay(APawn* InPawn)
{
    // �ൿ Ʈ�� ���� �� ������ �ʱ�ȭ
    if (UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComponent))
    {
        InitializeBlackboard(InPawn);

        // �ൿ Ʈ�� ����
        RunBehaviorTree(BehaviorTreeAsset);
    }
}

void AAIC_Enemy_Base::InitializeBlackboard(APawn* InPawn)
{
    if (BlackboardComponent)
    {
        // �÷��̾� ĳ���͸� �����忡 ����
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        APawn* PlayerPawn = PlayerController ? PlayerController->GetPawn() : nullptr;

        if (PlayerPawn)
        {
            BlackboardComponent->SetValueAsObject(AttackTargetKeyName, PlayerPawn);
        }
    }
}