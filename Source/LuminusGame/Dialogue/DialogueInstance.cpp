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
    if (DialogueTable == NULL) {
        UE_LOG(LogTemp, Error, TEXT("NULL DialogueTable"));
        return;
    }

    // ������ ���̺��� ��� ���� �ݺ��Ͽ� �Ľ�
    const TArray<FName>& RowNames = DialogueTable->GetRowNames();
    for (const FName& RowName : RowNames)
    {
        // ������ ���̺��� Ư�� �̸��� ���� ��������
        FDialogueData* DialogueData = DialogueTable->FindRow<FDialogueData>(RowName, FString());
        if (DialogueData != nullptr)
        {
            // ������ �����͸� Map�� ����
            DialogueDataMap.Add(DialogueData->ID, *DialogueData);
        }
    }

    // �Ľ̵� �����͸� ����� �� �ֽ��ϴ�.
    // ���� ���, ID�� 1�� �����Ϳ� �����Ϸ��� ������ ���� �մϴ�.
    if (const FDialogueData* Data = DialogueDataMap.Find(1)) 
    {
        // û�� �ȳ��ϼ���.
        UE_LOG(LogTemp, Warning, TEXT("Name: %s, Context: %s"), *Data->Name.ToString(), *Data->Context.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Data"));
    }
}
