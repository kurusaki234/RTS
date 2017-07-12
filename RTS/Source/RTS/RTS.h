// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "RTSGameMode.h"
#include "RTSGameState.h"
#include "RTSPlayerController.h"
#include "InfantryUnits.h"

#define COLLISION_LANDSCAPE		ECC_GameTraceChannel1
#define COLLISION_WEAPON		ECC_GameTraceChannel2
#define COLLISION_PROJECTILE	ECC_GameTraceChannel3