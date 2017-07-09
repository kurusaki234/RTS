// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS.h"
#include "RTSGameMode.h"

ARTSGameMode::ARTSGameMode()
{

}

void ARTSGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

}

void ARTSGameMode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ARTSGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

float ARTSGameMode::ModifyDamage(float Damage, AActor * DamagedActor, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) const
{
	return 0.0f;
}
