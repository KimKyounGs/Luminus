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
            // 가져온 데이터를 Map에 저장
            DialogueDataMap.Add(DialogueData->ID, *DialogueData);
        }
    }

    // 파싱된 데이터를 사용할 수 있습니다.
    // 예를 들어, ID가 1인 데이터에 접근하려면 다음과 같이 합니다.
    if (const FDialogueData* Data = DialogueDataMap.Find(1)) 
    {
        // 청일 안녕하세요.
        UE_LOG(LogTemp, Warning, TEXT("Name: %s, Context: %s"), *Data->Name.ToString(), *Data->Context.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Data"));
    }
}
