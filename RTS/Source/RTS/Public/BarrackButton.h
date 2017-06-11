// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "BarrackButton.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadDelegate, FString, name);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UCLASS()
class RTS_API UBarrackButton : public UButton
{
	GENERATED_BODY()
	
public:
	UBarrackButton();
	
	UPROPERTY()
	FLoadDelegate Load;

	UPROPERTY()
	FClickDelegate Click;

	UFUNCTION()
	void OnClick();

	UFUNCTION() 
	void LoadGameFile(FString name);
};
