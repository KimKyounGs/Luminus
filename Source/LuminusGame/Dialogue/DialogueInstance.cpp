// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstance.h"
#include "Engine/DataTable.h" // 데이터 테이블 헤더 파일 포함


UDialogueInstance::UDialogueInstance()
{
	// 다이얼로그 데이터 테이블 가져오기.
	FString DialogueDataPath = TEXT("DataTable'/Game/GameData/DialogueData/Test'");
    static ConstructorHelpers::FObjectFinder<UDataTable> MyDataTableObject(*DialogueDataPath);
    if (MyDataTableObject.Succeeded())
    {
        DialogueTable = MyDataTableObject.Object;
        UE_LOG(LogTemp, Error, TEXT("Success to load data table: %s"), *DialogueDataPath);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load data table: %s"), *DialogueDataPath);
    }

    ParsingDataTable();
}

void UDialogueInstance::ParsingDataTable()
{
    if (DialogueTable == NULL) return;

    TArray<FDialogueData*> arr;

}
