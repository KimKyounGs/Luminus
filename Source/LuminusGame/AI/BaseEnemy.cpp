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
    UE_LOG(LogTemp, Warning, TEXT("Yes WieldSword()"));
    if (SwordClass) // 스폰할 검 클래스가 유효한지 확인
    {
        UE_LOG(LogTemp, Warning, TEXT("Yes SworldClass"));
        // 검 스폰
        FActorSpawnParameters SpawnParams;
        SpawnParams.Instigator = this;  // Instigator 설정

        // 캐릭터 위치에서 검을 스폰
        AActor* SpawnedSword = GetWorld()->SpawnActor<AActor>(SwordClass, GetActorTransform(), SpawnParams);

        if (SpawnedSword)
        {
            UE_LOG(LogTemp, Warning, TEXT("Yes SpawnSword"));
            USkeletalMeshComponent* MeshComp = GetMesh();

            if (MeshComp)
            {
                UE_LOG(LogTemp, Warning, TEXT("Yes MeshComp"));
                // 소켓에 검 부착
                FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
                SpawnedSword->AttachToComponent(MeshComp, AttachRules, SocketName);

                bIsWieldingSword = true;
            }
        }
    }
}