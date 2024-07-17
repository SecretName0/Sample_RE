// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIC_EnemyControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API AAIC_EnemyControllerBase : public AAIController
{
	GENERATED_BODY()
	
// ----------------------------------------------------------------------- //
	// Funcs

public:


protected:
	virtual void BeginPlay() override;

private:

// ----------------------------------------------------------------------- //
	// Value

public:
	UPROPERTY(EditAnywhere)
	UBlackboardData* BlackBoardData;
	UPROPERTY(EditAnywhere)
	UBlackboardComponent* BlackBoardComponent;

	APawn* Player;

protected:


private:
	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyTree;

};
