// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"

#include "LuminusGameInstance.generated.h"

// ��ȭ ����ü
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
class LUMINUSGAME_API ULuminusGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	UDataTable* DialogueTable; // ���̾�α� ���̺�

	TMap<int32, TArray<FDialogueData>> DialogueDataMap; // Map�� ���̾�α� ������ ����. 

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	USoundBase* BackgroundMusic;

public:
	// ���� �ν��Ͻ��� ������ -> Init ������ ����ȴ�.
	ULuminusGameInstance();
	virtual void Init() override;
	void ParsingDataTable(); // ������ �Ľ�
	const TArray<FDialogueData>& SendDialogueData(const int32 ID); // �ش� ID�� Map�� Ű�� ����ؼ� ��ȭ ������ ������.
};
