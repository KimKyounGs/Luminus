// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class LUMINUSGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	/*
	// 차사 능력치
	UPROPERTY()
	int Health;
	int Mana;
	*/
protected:
	virtual void BeginPlay() override;

public:	
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
