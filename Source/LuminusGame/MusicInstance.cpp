// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicInstance.h"
#include "Kismet/GameplayStatics.h"

UMusicInstance::UMusicInstance()
{
    if (BackgroundMusic)
    {
        UGameplayStatics::PlaySound2D(this, BackgroundMusic);
    }
}
