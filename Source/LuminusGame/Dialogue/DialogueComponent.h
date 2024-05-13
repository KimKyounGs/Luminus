// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUMINUSGAME_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

private:	
	FString EXString;
	
	UPROPERTY(EditAnywhere, Category = Ex)
	int ExNum;

protected:
	virtual void BeginPlay() override;

public:	
	UDialogueComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
