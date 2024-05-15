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
    if (DialogueTable == NULL) {
        UE_LOG(LogTemp, Error, TEXT("NULL DialogueTable"));
        return;
    }

    // 데이터 테이블의 모든 행을 반복하여 파싱
    const TArray<FName>& RowNames = DialogueTable->GetRowNames();
    for (const FName& RowName : RowNames)
    {
        // 데이터 테이블에서 특정 이름의 행을 가져오기
        FDialogueData* DialogueData = DialogueTable->FindRow<FDialogueData>(RowName, FString());
        if (DialogueData != nullptr)
        {
            // 가져온 데이터를 배열에 추가
            TArray<FDialogueData>& DialogueArray = DialogueDataMap.FindOrAdd(DialogueData->ID);
            DialogueArray.Add(*DialogueData);
        }
    }

    // EX) ID가 4인 데이터에 접근.
    if (const TArray<FDialogueData>* DataArray = DialogueDataMap.Find(4))
    {
        for (const FDialogueData& Data : *DataArray)
        {
            // 데이터 사용 예시
            UE_LOG(LogTemp, Warning, TEXT("Name: %s, Context: %s"), *Data.Name.ToString(), *Data.Context.ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Data"));
    }
}

const TArray<FDialogueData>& UDialogueInstance::SendDialogueData(const int32 ID)
{
    if (const TArray<FDialogueData>* DataArray = DialogueDataMap.Find(ID))
    {
        // **** 이제 여기서 대화 데이터를 보내면 됨. ****
        for (const FDialogueData& Data : *DataArray)
        {
            // 디버깅.
            UE_LOG(LogTemp, Warning, TEXT("Name: %s, Context: %s"), *Data.Name.ToString(), *Data.Context.ToString());
        }
        return *DataArray;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Data ID = %d"), ID);
        // 빈 배열을 반환.
        static const TArray<FDialogueData> EmptyArray;
        return EmptyArray;
    }
}