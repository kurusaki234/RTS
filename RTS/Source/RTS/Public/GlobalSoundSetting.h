// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GlobalSoundSetting.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UGlobalSoundSetting : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

        /**
        *   Change global volume setting in game.
        *   @param          InPlayerController - The player controller reference
        *   @param
        */
    UFUNCTION(BlueprintCallable, Category = "UI|Sound")
        static void SetMasterSound(USoundClass* InSoundClass, const float Volume);
	
};
