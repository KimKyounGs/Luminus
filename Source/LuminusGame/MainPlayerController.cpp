// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"


void AMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if(Subsystem != nullptr)
    {
        Subsystem->AddMappingContext(UIInputMappingContext, 0);
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this, &AMainPlayerController::ViewMainMenu);
    }

    HUD = CreateWidget(this, HUDScreenClass);
    MainMenu = CreateWidget(this, MainMenuScreenClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }

}

//메인메뉴 띄우기
void AMainPlayerController::ViewMainMenu()
{
    if(MainMenu != nullptr)
    {
        if(!IsViewMenu)
        {
            //SetPause(true);
            MainMenu->AddToViewport();
            bShowMouseCursor = true;
            SetInputMode(FInputModeUIOnly());
            IsViewMenu = true;
        }
        else
        {
            MainMenu->RemoveFromParent();
            bShowMouseCursor = false;
            SetInputMode(FInputModeGameOnly());
            IsViewMenu = false;
        }

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No MainMenu Widget! Please check PlayerController BP"));
    }

}
