// Copyright Epic Games, Inc. All Rights Reserved.

#include "LuminusGameCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Engine/DamageEvents.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ALuminusGameCharacter

ALuminusGameCharacter::ALuminusGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void ALuminusGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	PlayerController = Cast<AMainPlayerController>(Controller);
	//Add Input Mapping Context
	if (PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	CurrentHealth = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("시작 체력 : %f"),CurrentHealth);

}

float ALuminusGameCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount,DamageEvent,EventInstigator,DamageCauser);
	if(!isRolling)
	{
		CurrentHealth = CurrentHealth - DamageApplied;
	
		if(CurrentHealth < 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("You Die"));
		}	
	}
    return DamageApplied;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALuminusGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ALuminusGameCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALuminusGameCharacter::Move);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALuminusGameCharacter::Look);
		//확대
		EnhancedInputComponent->BindAction(ExpansionAction, ETriggerEvent::Triggered, this, &ALuminusGameCharacter::Expansion);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void ALuminusGameCharacter::Jump()
{
	if(isRolling || isAttacking)
	{
		return;
	}
	
	Super::Jump();

}


void ALuminusGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALuminusGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	float ControllerYaw;
	FRotator CameraRotation = GetController()->GetControlRotation();
	ControllerYaw = CameraRotation.Vector().Z;

	if (Controller != nullptr && !isLockOn)
	{
		if(ControllerYaw > 0.2f && LookAxisVector.Y < 0)
		{
			AddControllerYawInput(LookAxisVector.X); 	
		}
		else if(ControllerYaw < -0.9f && LookAxisVector.Y > 0)
		{
			AddControllerYawInput(LookAxisVector.X); 
		}
		else
		{
			// add yaw and pitch input to controller
			AddControllerYawInput(LookAxisVector.X); 
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void ALuminusGameCharacter::Expansion(const FInputActionValue& Value)
{
	float Input = Value.Get<float>();

	float ArmLength = CameraBoom->TargetArmLength;

	if(Input == -1 && ArmLength <= 500)
	{
		ArmLength += 50;
	}
	else if(Input == 1 && ArmLength >= 100)
	{
		ArmLength -= 50;
	}

	CameraBoom->TargetArmLength = ArmLength;

}

const UInputAction* GetInputActionFromMappingContext(UInputMappingContext* MappingContext, FName ActionName)
{
    if (!MappingContext) return nullptr;

    const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();

    for (const FEnhancedActionKeyMapping& Mapping : Mappings)
    {
        if (Mapping.Action && Mapping.Action->GetFName() == ActionName)
        {
            return Mapping.Action.Get();
        }
    }

    return nullptr;
}