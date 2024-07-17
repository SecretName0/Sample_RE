// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterBase.generated.h"

UCLASS()
class SAMPLE_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

// ----------------------------------------------------------------------- //
	// Funcs

public:
	ACharacterBase();

	virtual void Tick(float DeltaTime) override;

	// Take Damage ------------------------------------------------------- //
	/*virtual float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;*/

	// Melee Action ------------------------------------------------------ //
	UFUNCTION()
	void OnMeleeAreaOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
	void DisableMeleeTrigger();

	UFUNCTION(BlueprintCallable, Category = "Down->StandUP")
	void StandUp();

	void MeleeType_ComboAttack();
	void GunType_Fire();
	void JustMeleeAttack();

	UFUNCTION(BlueprintCallable)
	void CanNotAction();
	UFUNCTION(BlueprintCallable)
	void RecoveryActionState();

protected:
	virtual void BeginPlay() override;

private:
	void KnockBack(ACharacter* HitCharacter, float KnockbackPower);

	void CanActionStateReset();

	void SetAttackOptions();

	void SetMovementSpeed();

	// Attack State Admin ================================================ //
	void InitAttackState();
	void NowAttack();
	void StateInitTimer(float Delay);

// ----------------------------------------------------------------------- //
		// Value

public:
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float MaxHP;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float CurHP;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float AggressiveStrength;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float MeleeStrength;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float ProjectileStrength;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float Defense;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float KnockBackPower;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float MoveSpeed; // 이동 속도 값은 모두가 가져야함
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float AttackDelay;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float MeleeDelay;
	UPROPERTY(EditAnywhere, Category = "Common Combat Stat", BlueprintReadWrite)
	float FireMaxRange;
	// ------------------------------------------------ //
	UPROPERTY(EditAnywhere, Category = "Common Anim State Boolean", BlueprintReadWrite)
	bool IsMoving; // 실질적으론 스테이트 점검용으로만 사용
	UPROPERTY(EditAnywhere, Category = "Common Anim State Boolean", BlueprintReadWrite)
	bool CurFooling; // 실질적으론 스테이트 점검용으로만 사용
	UPROPERTY(EditAnywhere, Category = "Common Anim State Boolean", BlueprintReadWrite)
	bool IsDead;
	UPROPERTY(EditAnywhere, Category = "Common Anim State Boolean", BlueprintReadWrite)
	bool IsDown;
	// ------------------------------------------------ //
	UPROPERTY(EditAnywhere, Category = "Character State Boolean", BlueprintReadWrite)
	bool CanAction;
	UPROPERTY(EditAnywhere, Category = "Character State Boolean", BlueprintReadWrite)
	bool CanAttack; // 총기 발사등 일반 공격
	UPROPERTY(EditAnywhere, Category = "Character State Boolean", BlueprintReadWrite)
	bool CanMelee; // 밀치기등의 근접 공격
	UPROPERTY(EditAnywhere, Category = "Character State Boolean", BlueprintReadWrite)
	bool CanControlCamera; // 카메라를 통한 시점 돌리기
	UPROPERTY(EditAnywhere, Category = "Character State Boolean", BlueprintReadWrite)
	bool WeakPointBreak;
	UPROPERTY(EditAnywhere, Category = "Character State Boolean", BlueprintReadWrite)
	bool ChangePointBreak;
	// ------------------------------------------------ //
	UPROPERTY(EditAnywhere, Category = "Common Anim Montage")
	UAnimMontage* FireMontage;
	UPROPERTY(EditAnywhere, Category = "Common Anim Montage")
	UAnimMontage* MeleeMontage;

protected:
	UPROPERTY(EditAnywhere, Category = "Common Parts Action Value", BlueprintReadWrite)
	int PointDamage; // 필요에따라 다른 값 지정

	UPROPERTY(EditAnywhere, Category = "Common Parts Action Value", BlueprintReadWrite)
	int BreakPointHP; // 해당 캐릭터에서 값 지정
	UPROPERTY(EditAnywhere, Category = "Common Parts Action Value", BlueprintReadWrite)
	FName BreakPoint; // 해당 캐릭터에서 값 지정
	void BreakPartsCalculating(int BreakPointDamage);
	void BreakParts();

	UPROPERTY(EditAnywhere, Category = "Common Parts Action Value", BlueprintReadWrite)
	int ChangePointHP; // 해당 캐릭터에서 값 지정
	UPROPERTY(EditAnywhere, Category = "Common Parts Action Value", BlueprintReadWrite)
	FName ChangePoint; // 해당 캐릭터에서 값 지정
	/* 체인지할 다른 액터 클래스 추가 필요
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMyGun> GunClass;

	AMyGun* Gun;
	*/
	void ChangingPartsCalculating(int PointDamaged);
	void ChangingParts();

	FCollisionQueryParams Params;

	UPROPERTY(VisibleAnywhere, Category = "Move Component")
	UCharacterMovementComponent* MoveComponent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* MeleeArea;

};
