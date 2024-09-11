#include "BaseEnemy.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

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

TArray<AActor*> ABaseEnemy::GetPatrolRoute() const
{
    return PatrolRoute;
}

float ABaseEnemy::SetMovementSpeed(EMovementStatus Speed)
{
    float SpeedValue = 0.0f;

    // ������ ���¿� ���� �ӵ� �� ����
    switch (Speed)
    {
    case EMovementStatus::Idle:
        SpeedValue = 0.0f;
        break;
    case EMovementStatus::Walking:
        SpeedValue = 100.0f; // �������� ���̴� Walking �ӵ�
        break;
    case EMovementStatus::Jogging:
        SpeedValue = 300.0f; // �������� ���̴� Jogging �ӵ�
        break;
    case EMovementStatus::Sprinting:
        SpeedValue = 500.0f; // �������� ���̴� Sprinting �ӵ�
        break;
    default:
        break;
    }

    // ĳ������ Max Walk Speed�� ����
    GetCharacterMovement()->MaxWalkSpeed = SpeedValue;
    return SpeedValue;
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
        // ������ �������� �˸��� ��������Ʈ ȣ��
        OnAttackEnd.Broadcast();
    }
}

// ���� �����ϰ� �����ϴ� �Լ�
void ABaseEnemy::WieldSword()
{
    if (SwordClass) // ������ �� Ŭ������ ��ȿ���� Ȯ��
    {
        // �� ����
        FActorSpawnParameters SpawnParams;
        SpawnParams.Instigator = this;  // Instigator ����

        // ĳ���� ��ġ���� ���� ����
        AActor* SpawnedSword = GetWorld()->SpawnActor<AActor>(SwordClass, GetActorTransform(), SpawnParams);

        if (SpawnedSword)
        {
            USkeletalMeshComponent* MeshComp = GetMesh();

            if (MeshComp)
            {
                // ���Ͽ� �� ����
                FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
                SpawnedSword->AttachToComponent(MeshComp, AttachRules, SocketName);

                bIsWieldingSword = true;
            }
        }
    }
}