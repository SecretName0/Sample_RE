#include "ACO_PlayerControllerBase.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_PlayerControllerBase.h"

AACO_PlayerControllerBase::AACO_PlayerControllerBase()
{
    PrimaryActorTick.bCanEverTick = true;

	OwnerPlayer = Cast<AC_PlayableBase>(GetOwner());
}

void AACO_PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

}
