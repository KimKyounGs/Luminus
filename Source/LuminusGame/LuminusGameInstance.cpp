// Fill out your copyright notice in the Description page of Project Settings.


#include "LuminusGameInstance.h"
#include "Engine/DataTable.h" 
#include "Kismet/GameplayStatics.h"

ULuminusGameInstance::ULuminusGameInstance()
{
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

}

void ULuminusGameInstance::Init()
{
    Super::Init();

    if (BackgroundMusic)
    {
        UGameplayStatics::PlaySound2D(this, BackgroundMusic);
    }

    ParsingDataTable();
}

void ULuminusGameInstance::ParsingDataTable()
{
    if (DialogueTable == NULL) {
        UE_LOG(LogTemp, Error, TEXT("NULL DialogueTable"));
        return;
    }

    const TArray<FName>& RowNames = DialogueTable->GetRowNames();
    for (const FName& RowName : RowNames)
    {
        FDialogueData* DialogueData = DialogueTable->FindRow<FDialogueData>(RowName, FString());
        if (DialogueData != nullptr)
        {
            TArray<FDialogueData>& DialogueArray = DialogueDataMap.FindOrAdd(DialogueData->ID);
            DialogueArray.Add(*DialogueData);
        }
    }

    if (const TArray<FDialogueData>* DataArray = DialogueDataMap.Find(4))
    {
        for (const FDialogueData& Data : *DataArray)
        {
            UE_LOG(LogTemp, Warning, TEXT("Name: %s, Context: %s"), *Data.Name.ToString(), *Data.Context.ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Data"));
    }
}

const TArray<FDialogueData>& ULuminusGameInstance::SendDialogueData(const int32 ID)
{
    if (const TArray<FDialogueData>* DataArray = DialogueDataMap.Find(ID))
    {
        for (const FDialogueData& Data : *DataArray)
        {
            UE_LOG(LogTemp, Warning, TEXT("Name: %s, Context: %s"), *Data.Name.ToString(), *Data.Context.ToString());
        }
        return *DataArray;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Can't Find Data ID = %d"), ID);
        static const TArray<FDialogueData> EmptyArray;
        return EmptyArray;
    }
}
