// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class LUMINUSGAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* UIInputMappingContext;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDScreenClass;

	void ViewMainMenu();

protected:
	virtual void BeginPlay();

private:
	UPROPERTY()
	UUserWidget* HUD;

	UPROPERTY()
	UUserWidget* MainMenu;
	
	bool IsViewMenu = false;
};
