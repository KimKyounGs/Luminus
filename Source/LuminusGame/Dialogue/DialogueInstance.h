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
	UDataTable* DialogueTable; // 다이얼로그 테이블
	TMap<int32, TArray<FDialogueData>> DialogueDataMap; // Map에 다이얼로그 데이터 저장. 
public:
	UDialogueInstance(); // 생성자
	void ParsingDataTable(); // 데이터 파싱
	const TArray<FDialogueData>& SendDialogueData(const int32 ID); // 해당 ID를 Map의 키로 사용해서 대화 데이터 보내기.
};
