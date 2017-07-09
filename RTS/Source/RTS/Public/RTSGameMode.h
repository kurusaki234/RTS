// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "RTSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API ARTSGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ARTSGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	TSubclassOf<APawn> BotPawnClass;

	virtual void PreInitializeComponents() override;

	// Initialize the game. This is called before actors'
	// PreInitializeComponents().
	virtual void InitGame(const FString& MapName, const FString& Options,
		FString& ErrorMessage) override;

	// Starts match warmup 
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Prevents friendly fire
	virtual float ModifyDamage(float Damage, AActor* DamagedActor,
		struct FDamageEvent const& DamageEvent, AController* EventInstigator,
		AActor* DamageCauser) const;
	
	
};
