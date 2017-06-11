// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "BarrackButton.h"

UBarrackButton::UBarrackButton()
{
	OnClicked.AddDynamic(this, &UBarrackButton::OnClick);

	Load.AddDynamic(this, &UBarrackButton::LoadGameFile);
}

void UBarrackButton::OnClick()
{
	Load.Broadcast("1231");

	APlayerController* PlayerController = Cast <APlayerController>(GetWorld()->GetFirstPlayerController());

	float mouseX = 0, mouseY = 0;
	FVector mouseLocation, mouseDirection;

	PlayerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
	//GetWorld()->LineTraceSingleByChannel()
}

void UBarrackButton::LoadGameFile(FString name)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *name);
}
