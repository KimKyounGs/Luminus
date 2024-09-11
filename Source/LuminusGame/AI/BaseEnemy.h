// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuminusGame/AI/EnemyInterface.h"
#include "BaseEnemy.generated.h"

// ��������Ʈ ����
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class LUMINUSGAME_API ABaseEnemy : public ACharacter, public IEnemyInterface
{
    GENERATED_BODY()

public:
    ABaseEnemy();

    // ���� �ִϸ��̼� ��Ÿ��
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage* AttackMontage;

    // ������ ������ �� ȣ��� ��������Ʈ
    UPROPERTY(BlueprintAssignable, Category = "Attack")
    FOnAttackEndDelegate OnAttackEnd;

    // ��� ���� (MyCharacter.h �Ǵ� �ʿ��� Ŭ���� ����� �߰�)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AActor> SwordClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
    bool bIsWieldingSword;

    // ���� ��θ� �����ϴ� ����
    UPROPERTY(EditAnywhere, Category = "AI")
    TArray<FVector> PatrolRoute;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // �ִϸ��̼��� ������ �� ȣ��� �Լ�
    void OnMontageCompleted(UAnimMontage* Montage, bool bInterrupted);

public :
    virtual TArray<FVector> GetPatrolRoute() const override;

    virtual float SetMovementSpeed(EMovementStatus Speed) override;

    // ���� �Լ� (�ִϸ��̼��� ���)
    UFUNCTION(BlueprintCallable, Category = "Attack")
    void Attack();

    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void WieldSword();



private:
    // ���� �̸� ����
    FName SocketName = TEXT("Enemy1Weapon_r");
};
