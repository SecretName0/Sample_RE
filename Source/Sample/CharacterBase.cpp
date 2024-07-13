// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeleeArea = CreateDefaultSubobject<UBoxComponent>
		(TEXT("Melee Attack Area"));
	MeleeArea->SetupAttachment(GetMesh(),
		TEXT("Melee Attack Area"));
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	MeleeArea->OnComponentBeginOverlap.AddDynamic(this,
		&ACharacterBase::OnMeleeAreaOverlapBegin);

	CanAction = true;

	SetMovementSpeed();
	SetAttackOptions();
	DisableMeleeTrigger();
	InitAttackState();
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::OnMeleeAreaOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Error, TEXT("Melee call"));
	if (OtherActor && OtherActor != this)
	{
		//UE_LOG(LogTemp, Error, TEXT("Actor Overlap"));

		// 피격자가 플레이어고 공격자가 탱크일 때만
		if (OtherActor->ActorHasTag("Player") && ActorHasTag("Tank"))
		{
			//UE_LOG(LogTemp, Error, TEXT("Player Overlap"));
			ACharacter* HitCharacter = Cast<ACharacter>(OtherActor);
			KnockBack(HitCharacter, 1000);
		}

		UGameplayStatics::ApplyDamage(OtherActor, MeleeStrength,
			GetController(), this, nullptr);
	}
}

void ACharacterBase::DisableMeleeTrigger()
{
	MeleeArea->SetGenerateOverlapEvents(false);
	//UE_LOG(LogTemp, Error, TEXT("Melee Disable"));
}

void ACharacterBase::KnockBack(ACharacter* HitCharacter, float KnockbackPower)
{
	FVector AtkDir = HitCharacter->GetActorLocation() - GetActorLocation();
	AtkDir.Normalize();
	FVector KnockBackDistance = AtkDir * KnockbackPower;

	HitCharacter->LaunchCharacter(KnockBackDistance, false, false);
}

void ACharacterBase::CanActionStateReset()
{
	CanAction = true;
}

void ACharacterBase::SetAttackOptions()
{
	Params.AddIgnoredActor(this);
	// 이후 필요에따라 오폭 범위 설정
}

void ACharacterBase::SetMovementSpeed()
{
	MoveComponent = GetCharacterMovement();
	MoveComponent->MaxWalkSpeed = MoveSpeed;
}

void ACharacterBase::StandUp()
{
	IsDown = false;

	FTimerHandle ActionTimer;
	GetWorldTimerManager().SetTimer(ActionTimer, this,
		&ACharacterBase::CanActionStateReset, 1, false);
}

void ACharacterBase::MeleeType_ComboAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee Combo"));
}

void ACharacterBase::JustMeleeAttack()
{
	UE_LOG(LogTemp, Error, TEXT("Melee Call"));
}

void ACharacterBase::GunType_Fire()
{
	if (CanAttack && CanAction)
	{
		NowAttack();

		AController* ShooterController;
		FVector CurrentLocation;
		FRotator CurrentRotation;
		// ------------------------------- //
		ShooterController = this->GetController();

		if (ShooterController == nullptr)
			return;

		ShooterController->GetPlayerViewPoint(CurrentLocation, CurrentRotation);

		FVector ShotDirection = -CurrentRotation.Vector();

		FHitResult HitResult;

		PlayAnimMontage(FireMontage);

		FVector InRange = CurrentLocation + CurrentRotation.Vector() * FireMaxRange;

		bool bSuccessHit = GetWorld()->LineTraceSingleByChannel(HitResult,
			CurrentLocation, InRange, ECC_GameTraceChannel1, Params);

		if (bSuccessHit)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor != nullptr)
			{
				FPointDamageEvent DamageEvent(AggressiveStrength, HitResult,
					ShotDirection, nullptr);

				float GiveDamage = AggressiveStrength;

				// 약점 명중
				if (HitResult.BoneName == BreakPoint)
				{
					GiveDamage *= 2; // 약점 메리트

					//UE_LOG(LogTemp, Warning, TEXT("<<< HeadShot >>>"));
					//UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), GiveDamage);

					HitActor->TakeDamage(GiveDamage, DamageEvent, ShooterController,
						this);
				}

				// 교체 가능 부위 명중
				else if (HitResult.BoneName == ChangePoint)
				{
					//UE_LOG(LogTemp, Warning, TEXT("<<< HeadShot >>>"));
					//UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), GiveDamage);

					HitActor->TakeDamage(GiveDamage, DamageEvent, ShooterController,
						this);
				}

				// 일반 명중
				else
				{
					//UE_LOG(LogTemp, Display, TEXT("--- Normal ---"));
					//UE_LOG(LogTemp, Display, TEXT("Damage: %f"), GiveDamage);

					HitActor->TakeDamage(GiveDamage, DamageEvent, ShooterController,
						this);
				}

				UE_LOG(LogTemp, Error, TEXT("Hit Point: %s"), *HitResult.BoneName.ToString());
			}
		}

		StateInitTimer(AttackDelay);
	}
}


void ACharacterBase::InitAttackState()
{
	CanAttack = true;
	CanMelee = true;
}

void ACharacterBase::NowAttack()
{
	CanAttack = false;
	CanMelee = false;
}

void ACharacterBase::StateInitTimer(float Delay)
{
	FTimerHandle DelayTimer;
	GetWorldTimerManager().SetTimer(DelayTimer, this,
		&ACharacterBase::InitAttackState, Delay, false);
}

void ACharacterBase::BreakPartsCalculating(int BreakPointDamage)
{
	BreakPointHP -= BreakPointDamage;

	if (BreakPointHP <= 0)
	{
		WeakPointBreak = true;

		if (WeakPointBreak)
		{
			BreakParts();

			// IsDead
		}
	}
}

void ACharacterBase::BreakParts()
{
	GetMesh()->HideBoneByName(BreakPoint, EPhysBodyOp::PBO_Term);
	// Term: 숨길 부위의 하위 본들도 숨김
	GetMesh()->SetAllBodiesBelowSimulatePhysics(BreakPoint, false);
}

void ACharacterBase::ChangingPartsCalculating(int PointDamaged)
{
	ChangePointHP -= PointDamage;

	if (ChangePointHP <= 0)
	{
		ChangePointBreak = true;

		if (ChangePointBreak)
		{
			ChangingParts();
		}
	}
}

void ACharacterBase::ChangingParts()
{
	GetMesh()->HideBoneByName(ChangePoint, EPhysBodyOp::PBO_None);
	/* 교체 부위에 대한 소켓 정보 전달 및 클래스 지정
	Gun->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	*/
}


