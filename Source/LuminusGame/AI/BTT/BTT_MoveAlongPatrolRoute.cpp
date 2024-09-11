#include "BTT_MoveAlongPatrolRoute.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "LuminusGame/AI/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

UBTT_MoveAlongPatrolRoute::UBTT_MoveAlongPatrolRoute()
{
    NodeName = "Move Along Patrol Route";
}

EBTNodeResult::Type UBTT_MoveAlongPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UE_LOG(LogTemp, Warning, TEXT("Go UBTT_MoveAlongPatrolRoute"));
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* ControlledPawn = AIController ? AIController->GetPawn() : nullptr;

    if (!AIController || !ControlledPawn)
    {
        return EBTNodeResult::Failed;
    }

    // Get Patrol Route �������̽� ȣ���Ͽ� ���� ����Ʈ ��������
    TArray<AActor*> PatrolPoints;
    if (!GetPatrolRoute(ControlledPawn, PatrolPoints) || PatrolPoints.Num() == 0)
    {
        return EBTNodeResult::Failed;
    }
    UE_LOG(LogTemp, Warning, TEXT("Yes PatrolPoints"));

    // ���� ����� ���� ����Ʈ�� �̵�
    int32 PatrolIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("PatrolIndex"));

    if (PatrolPoints.IsValidIndex(PatrolIndex))
    {
        AIController->MoveToActor(PatrolPoints[PatrolIndex], 10.0f); // ���� �ݰ� 10
    }

    // �������Ʈ���� ������ Increment Patrol Route �Լ� ȣ��
    IncrementPatrolRoute(ControlledPawn);

    // �½�ũ �Ϸ�
    return EBTNodeResult::Succeeded;
}

bool UBTT_MoveAlongPatrolRoute::GetPatrolRoute(AActor* ControlledPawn, TArray<AActor*>& OutPatrolPoints) const
{
    if (IEnemyInterface* PatrolRouteInterface = Cast<IEnemyInterface>(ControlledPawn))
    {
        OutPatrolPoints = PatrolRouteInterface->GetPatrolRoute();
        return true;
    }

    return false;
}

void UBTT_MoveAlongPatrolRoute::IncrementPatrolRoute(AActor* ControlledPawn)
{
    // �������Ʈ���� ������ IncrementPatrolRoute �̺�Ʈ ȣ��
    UFunction* IncrementPatrolRouteFunction = ControlledPawn->FindFunction(FName("IncrementPatrolRoute"));
    if (IncrementPatrolRouteFunction)
    {
        UE_LOG(LogTemp, Warning, TEXT("IncrementPatrolRoute"));
        ControlledPawn->ProcessEvent(IncrementPatrolRouteFunction, nullptr);

        UE_LOG(LogTemp, Warning, TEXT("No IncrementPatrolRoute"));
    }
}
