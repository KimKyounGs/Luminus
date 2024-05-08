// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();


	
}


void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

FString UDialogueComponent::SendDialogue()
{
	EXString = "Hello";
	return EXString;
}