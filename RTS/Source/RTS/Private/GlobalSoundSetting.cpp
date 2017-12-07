    // Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "GlobalSoundSetting.h"

void UGlobalSoundSetting::SetMasterSound(USoundClass* InSoundClass, const float Volume)
{
    if (InSoundClass)
    {
        InSoundClass->Properties.Volume = Volume;
    }
}
