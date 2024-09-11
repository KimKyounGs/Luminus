#include "BTT_MoveAlongPatrolRoute.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LuminusGame/AI/EnemyInterface.h"
#include "Kismet/GameplayStatics.h"

UBTT_MoveAlongPatrolRoute::UBTT_MoveAlongPatrolRoute()
{
    NodeName = "Move Along Patrol Route";
}

EBTNodeResult::Type UBTT_MoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

    if (!AIController || !ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    // �������̽��� ���� PatrolRoute�� �����ɴϴ�.
    IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(ControlledPawn);
    if (!EnemyInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("ControlledPawn���� �������̽��� ã�� �� �����ϴ�."));
        return EBTNodeResult::Failed;
    }

    // �������̽����� TArray<FVector> Ÿ���� ��θ� �����ɴϴ�.
    TArray<FVector> PatrolRoute = EnemyInterface->GetPatrolRoute();
    if (PatrolRoute.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("PatrolRoute�� ��� �ֽ��ϴ�."));
        return EBTNodeResult::Failed;
    }

    // PatrolIndex�� �����ͼ� ��ȿ���� Ȯ���մϴ�.
    int32 PatrolIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("PatrolIndex"));
    if (!PatrolRoute.IsValidIndex(PatrolIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("��ȿ���� ���� PatrolIndex�Դϴ�."));
        return EBTNodeResult::Failed;
    }

    // AI�� �ش� ����Ʈ�� �̵���ŵ�ϴ�.
    FVector WorldLocation = PatrolRoute[PatrolIndex];
    AIController->MoveToLocation(WorldLocation, 10.0f);  // ���� �ݰ� 10.0

    // ���� ��� �ε��� ������Ʈ (���߿� �ʿ��� ���)
    // PatrolIndex += 1;
    // OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("PatrolIndex"), PatrolIndex);

    return EBTNodeResult::Succeeded;
}

// IncrementPatrolRoute �Լ�
void UBTT_MoveAlongPatrolRoute::IncrementPatrolRoute(USplineComponent* PatrolRouteSpline)
{
    // PatrolRouteSpline���� IncrementPatrolRoute �Լ� ȣ��
    UFunction* IncrementPatrolRouteFunction = PatrolRouteSpline->FindFunction(FName("IncrementPatrolRoute"));
    if (IncrementPatrolRouteFunction)
    {
        PatrolRouteSpline->ProcessEvent(IncrementPatrolRouteFunction, nullptr);
        UE_LOG(LogTemp, Warning, TEXT("IncrementPatrolRoute �Լ��� ȣ��Ǿ����ϴ�."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PatrolRouteSpline���� IncrementPatrolRoute �Լ��� ã�� �� �����ϴ�."));
    }
}