// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueInstance.h"
#include "Engine/DataTable.h" // ������ ���̺� ��� ���� ����


UDialogueInstance::UDialogueInstance()
{
	// ���̾�α� ������ ���̺� ��������.
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
