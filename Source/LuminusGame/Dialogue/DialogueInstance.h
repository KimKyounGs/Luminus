// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "DialogueInstance.generated.h"

USTRUCT()
struct FDialogueData :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int ID;

	UPROPERTY(EditAnywhere)
	FName Name;

	UPROPERTY(EditAnywhere)
	FText Context;

};

UCLASS()
class LUMINUSGAME_API UDialogueInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UDataTable* DialogueTable;
	TMap<int, FDialogueData> DialogueDataMap;
public:
	UDialogueInstance();
	void ParsingDataTable();
	FDialogueData GetDialogueData();
};
