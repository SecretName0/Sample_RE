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

	// 블루 프린트로 이용중이라 테스트 종료 후 필요 없을 시 삭제 무방
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value);
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Value);
	UFUNCTION(BlueprintCallable)
	void RotatePitch(float Value);
	UFUNCTION(BlueprintCallable)
	void RotateYaw(float Value);

	// 점프키는 설정에 없어 굳이 넣지 않음
	UFUNCTION(BlueprintCallable)
	void Attack();
	UFUNCTION(BlueprintCallable)
	void MeleeAttack();

protected:


private:
	

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
