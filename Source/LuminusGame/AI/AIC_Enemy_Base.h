// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIC_Enemy_Base.generated.h"


// AI 상태 열거형 (패시브, 공격 상태 등)
//UENUM(BlueprintType)
//enum class EAIState : uint8
//{
//    Passive UMETA(DisplayName = "Passive"),
//    Attacking UMETA(DisplayName = "Attacking")
//};

UCLASS()
class LUMINUSGAME_API AAIC_Enemy_Base : public AAIController
{
	GENERATED_BODY()

public:
    AAIC_Enemy_Base();
protected:
    virtual void OnPossess(APawn* InPawn) override;

    // 행동 트리와 블랙보드 자산
    UPROPERTY(EditAnywhere, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(EditAnywhere, Category = "AI")
    UBlackboardComponent* BlackboardComponent;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FName AttackTargetKeyName;

    // 행동 트리 실행과 블랙보드 값 설정을 위한 함수
    void InitializeBlackboard(APawn* InPawn);

    // 지연 작업 (Delay)를 위한 타이머
    void StartBehaviorAfterDelay(APawn* InPawn);
};
