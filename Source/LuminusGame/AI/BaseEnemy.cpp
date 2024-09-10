#include "BaseEnemy.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
    // Set this character to call Tick() every frame
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseEnemy::Attack()
{
    if (AttackMontage && GetMesh())
    {
        UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
        if (AnimInstance)
        {
            // �ִϸ��̼� ��Ÿ�� ���
            float MontagePlayResult = AnimInstance->Montage_Play(AttackMontage, 1.0f);
            if (MontagePlayResult == 0.0f)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to play montage!"));
                return;
            }
            // �ִϸ��̼��� ������ �� OnMontageCompleted �Լ��� ȣ���ϵ��� ��������Ʈ ����
            FOnMontageEnded EndDelegate;
            EndDelegate.BindUObject(this, &ABaseEnemy::OnMontageCompleted);

            AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
        }
    }
}

void ABaseEnemy::OnMontageCompleted(UAnimMontage* Montage, bool bInterrupted)
{
    // ���� �ִϸ��̼��� �������� Ȯ���ϰ�, �����ٸ� OnAttackEnd ��������Ʈ�� ȣ��
    if (Montage == AttackMontage && !bInterrupted)
    {
        UE_LOG(LogTemp, Warning, TEXT("Attack finished, calling OnAttackEnd"));

        // ������ �������� �˸��� ��������Ʈ ȣ��
        OnAttackEnd.Broadcast();
    }
}