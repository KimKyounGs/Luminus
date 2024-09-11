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

    // 열거형 상태에 따른 속도 값 설정
    switch (Speed)
    {
    case EMovementStatus::Idle:
        SpeedValue = 0.0f;
        break;
    case EMovementStatus::Walking:
        SpeedValue = 100.0f; // 사진에서 보이는 Walking 속도
        break;
    case EMovementStatus::Jogging:
        SpeedValue = 300.0f; // 사진에서 보이는 Jogging 속도
        break;
    case EMovementStatus::Sprinting:
        SpeedValue = 500.0f; // 사진에서 보이는 Sprinting 속도
        break;
    default:
        break;
    }

    // 캐릭터의 Max Walk Speed를 설정
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
            // 애니메이션 몽타주 재생
            float MontagePlayResult = AnimInstance->Montage_Play(AttackMontage, 1.0f);
            if (MontagePlayResult == 0.0f)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to play montage!"));
                return;
            }
            // 애니메이션이 끝났을 때 OnMontageCompleted 함수를 호출하도록 델리게이트 설정
            FOnMontageEnded EndDelegate;
            EndDelegate.BindUObject(this, &ABaseEnemy::OnMontageCompleted);

            AnimInstance->Montage_SetEndDelegate(EndDelegate, AttackMontage);
        }
    }
}

void ABaseEnemy::OnMontageCompleted(UAnimMontage* Montage, bool bInterrupted)
{
    // 공격 애니메이션이 끝났는지 확인하고, 끝났다면 OnAttackEnd 델리게이트를 호출
    if (Montage == AttackMontage && !bInterrupted)
    {
        // 공격이 끝났음을 알리는 델리게이트 호출
        OnAttackEnd.Broadcast();
    }
}

// 검을 생성하고 부착하는 함수
void ABaseEnemy::WieldSword()
{
    if (SwordClass) // 스폰할 검 클래스가 유효한지 확인
    {
        // 검 스폰
        FActorSpawnParameters SpawnParams;
        SpawnParams.Instigator = this;  // Instigator 설정

        // 캐릭터 위치에서 검을 스폰
        AActor* SpawnedSword = GetWorld()->SpawnActor<AActor>(SwordClass, GetActorTransform(), SpawnParams);

        if (SpawnedSword)
        {
            USkeletalMeshComponent* MeshComp = GetMesh();

            if (MeshComp)
            {
                // 소켓에 검 부착
                FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
                SpawnedSword->AttachToComponent(MeshComp, AttachRules, SocketName);

                bIsWieldingSword = true;
            }
        }
    }
}