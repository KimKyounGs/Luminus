// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

// 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class LUMINUSGAME_API ABaseEnemy : public ACharacter
{
    GENERATED_BODY()

public:
    ABaseEnemy();

    // 공격 애니메이션 몽타주
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;

    // 공격 함수 (애니메이션을 재생)
    UFUNCTION(BlueprintCallable, Category = "Attack")
    void Attack();

    // 공격이 끝났을 때 호출될 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Attack")
    FOnAttackEndDelegate OnAttackEnd;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // 애니메이션이 끝났을 때 호출될 함수
    void OnMontageCompleted(UAnimMontage* Montage, bool bInterrupted);
};
