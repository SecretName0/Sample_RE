// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorBase.h"
#include "CharacterBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ACO_PlayerControllerBase.h"
#include "AIC_EnemyControllerBase.h"
#include "ProjectileBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API AProjectileBase : public AActorBase
{
	GENERATED_BODY()
	
// ----------------------------------------------------------------------- //
	// Funcs

public:
	AProjectileBase();

	UPROPERTY(EditAnywhere, Category = "Projectile Option")
	float ProjectileMaxSpeed;
	UPROPERTY(EditAnywhere, Category = "Projectile Option")
	float ProjectileInitialSpeed;
protected:


private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void GetTargetData(AActor* Actor);

// ----------------------------------------------------------------------- //
	// Value

public:


protected:


private:
	UPROPERTY(EditAnywhere, Category = "Projectile Option")
	UProjectileMovementComponent* PMC;

	ACharacterBase* HitTarget;
};
