// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayableBase.h"
#include "ACO_PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API AACO_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
// ----------------------------------------------------------------------- //
	// Funcs

public:
	AACO_PlayerControllerBase();

protected:
	virtual void BeginPlay() override;

private:
	

// ----------------------------------------------------------------------- //
	// Value

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AC_PlayableBase* OwnerPlayer;

protected:


private:
	
};
