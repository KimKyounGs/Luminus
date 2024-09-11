// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuminusGame/AI/EnemyInterface.h"
#include "BaseEnemy.generated.h"

// 델리게이트 선언
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class LUMINUSGAME_API ABaseEnemy : public ACharacter, public IEnemyInterface
{
    GENERATED_BODY()

public:
    ABaseEnemy();

    // 공격 애니메이션 몽타주
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;

    // 공격이 끝났을 때 호출될 델리게이트
    UPROPERTY(BlueprintAssignable, Category = "Attack")
    FOnAttackEndDelegate OnAttackEnd;

    // 헤더 파일 (MyCharacter.h 또는 필요한 클래스 헤더에 추가)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AActor> SwordClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    bool bIsWieldingSword;

    // 순찰 경로를 저장하는 변수
    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<FVector> PatrolRoute;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // 애니메이션이 끝났을 때 호출될 함수
    void OnMontageCompleted(UAnimMontage* Montage, bool bInterrupted);

public :
    virtual TArray<FVector> GetPatrolRoute() const override;

    virtual float SetMovementSpeed(EMovementStatus Speed) override;

    // 공격 함수 (애니메이션을 재생)
    UFUNCTION(BlueprintCallable, Category = "Attack")
    void Attack();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void WieldSword();



private:
    // 소켓 이름 정의
    FName SocketName = TEXT("Enemy1Weapon_r");
};
