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

    // 인터페이스를 통해 PatrolRoute를 가져옵니다.
    IEnemyInterface* EnemyInterface = Cast<IEnemyInterface>(ControlledPawn);
    if (!EnemyInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("ControlledPawn에서 인터페이스를 찾을 수 없습니다."));
        return EBTNodeResult::Failed;
    }

    // 인터페이스에서 TArray<FVector> 타입의 경로를 가져옵니다.
    TArray<FVector> PatrolRoute = EnemyInterface->GetPatrolRoute();
    if (PatrolRoute.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("PatrolRoute가 비어 있습니다."));
        return EBTNodeResult::Failed;
    }

    // PatrolIndex를 가져와서 유효한지 확인합니다.
    int32 PatrolIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(TEXT("PatrolIndex"));
    if (!PatrolRoute.IsValidIndex(PatrolIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("유효하지 않은 PatrolIndex입니다."));
        return EBTNodeResult::Failed;
    }

    // AI를 해당 포인트로 이동시킵니다.
    FVector WorldLocation = PatrolRoute[PatrolIndex];
    AIController->MoveToLocation(WorldLocation, 10.0f);  // 수용 반경 10.0

    // 순찰 경로 인덱스 업데이트 (나중에 필요한 경우)
    // PatrolIndex += 1;
    // OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("PatrolIndex"), PatrolIndex);

    return EBTNodeResult::Succeeded;
}

// IncrementPatrolRoute 함수
void UBTT_MoveAlongPatrolRoute::IncrementPatrolRoute(USplineComponent* PatrolRouteSpline)
{
    // PatrolRouteSpline에서 IncrementPatrolRoute 함수 호출
    UFunction* IncrementPatrolRouteFunction = PatrolRouteSpline->FindFunction(FName("IncrementPatrolRoute"));
    if (IncrementPatrolRouteFunction)
    {
        PatrolRouteSpline->ProcessEvent(IncrementPatrolRouteFunction, nullptr);
        UE_LOG(LogTemp, Warning, TEXT("IncrementPatrolRoute 함수가 호출되었습니다."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PatrolRouteSpline에서 IncrementPatrolRoute 함수를 찾을 수 없습니다."));
    }
}