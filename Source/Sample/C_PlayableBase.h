// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "C_PlayableBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLE_API AC_PlayableBase : public ACharacterBase
{
	GENERATED_BODY()
	
// ----------------------------------------------------------------------- //
	// Funcs

public:
	AC_PlayableBase();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:


private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotatePitch(float Value);
	void RotateYaw(float Value);

	// 점프키는 설정에 없어 굳이 넣지 않음
	void Attack();
	void MeleeAttack();

// ----------------------------------------------------------------------- //
		// Value

public:
	UPROPERTY(EditAnywhere, Category = "Option Setting")
	float MouseSensitivity = 15;

	UPROPERTY(EditAnywhere, Category = "Combat Stat")
	bool MaxRange;

protected:


private:
	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* Camera;

};
