// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sound/SoundBase.h"
#include "MusicInstance.generated.h"

UCLASS()
class LUMINUSGAME_API UMusicInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundBase* BackgroundMusic;

public:
	UMusicInstance();
};
