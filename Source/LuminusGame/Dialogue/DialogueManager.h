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
	// csv���� �ؼ��ϴ� �Լ�.
	void ReadCSVFile(const FString& FilePath);
	// ��ȭ �������� �Լ�
private:

};
