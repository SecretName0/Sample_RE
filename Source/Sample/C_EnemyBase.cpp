// Fill out your copyright notice in the Description page of Project Settings.


#include "C_EnemyBase.h"

AC_EnemyBase::AC_EnemyBase()
{
	FinishPoint = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	FinishPoint->SetupAttachment(RootComponent);
}
