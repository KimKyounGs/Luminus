// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIC_Enemy_Base.generated.h"


// AI ���� ������ (�нú�, ���� ���� ��)
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

    // �ൿ Ʈ���� ������ �ڻ�
    UPROPERTY(EditAnywhere, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    UPROPERTY(EditAnywhere, Category = "AI")
    UBlackboardComponent* BlackboardComponent;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
    FName AttackTargetKeyName;

    // �ൿ Ʈ�� ����� ������ �� ������ ���� �Լ�
    void InitializeBlackboard(APawn* InPawn);

    // ���� �۾� (Delay)�� ���� Ÿ�̸�
    void StartBehaviorAfterDelay(APawn* InPawn);
};
