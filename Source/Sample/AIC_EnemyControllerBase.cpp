// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_EnemyControllerBase.h"
#include "Kismet/GameplayStatics.h"

void AAIC_EnemyControllerBase::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyTree != nullptr)
	{
		RunBehaviorTree(EnemyTree);

		UseBlackboard(BlackBoardData, BlackBoardComponent);

		Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		// �÷��̾ �������� �˷���
	}
}
