// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class LUMINUSGAME_API DialogueManager
{
public:
	DialogueManager();
	~DialogueManager();
	// csv파일 해석하는 함수.
	void ReadCSVFile(const FString& FilePath);
	// 대화 내보내는 함수
private:

};
