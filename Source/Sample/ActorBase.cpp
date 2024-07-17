// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorBase.h"

AActorBase::AActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = RootComp;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>
		(TEXT("Projectile Mesh"));
	ActorMesh->SetupAttachment(RootComp);
}

void AActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

