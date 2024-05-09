// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DialogueInstance.generated.h"

class UDataTable;

UCLASS()
class LUMINUSGAME_API UDialogueInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UDataTable* DialogueTable;

public:
	UDialogueInstance();

};
