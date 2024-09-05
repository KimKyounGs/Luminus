// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class LUMINUSGAME_API UBTT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
    UBTT_MeleeAttack();

protected:
    /** Starts task, should return Succeeded, Failed or InProgress */
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    /** The animation montage to play when attacking */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UAnimMontage* MeleeAttackMontage;
};
