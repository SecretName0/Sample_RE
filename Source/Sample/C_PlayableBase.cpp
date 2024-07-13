// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayableBase.h"

AC_PlayableBase::AC_PlayableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f; 
	SpringArm->bEnableCameraLag = false; // Ȱ��ȭ ����� true
	// SpringArm->CameraLagSpeed = 3.0f; ī�޶� ������ �ʿ��� ��� �������

	// Camera Component ���� �� ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AC_PlayableBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AC_PlayableBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AC_PlayableBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("CameraPitchRotate"), this, &AC_PlayableBase::RotatePitch);
	PlayerInputComponent->BindAxis(TEXT("CameraYawRotate"), this, &AC_PlayableBase::RotateYaw);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AC_PlayableBase::Attack);
	PlayerInputComponent->BindAction(TEXT("Melee"), IE_Pressed, this, &AC_PlayableBase::MeleeAttack);
}

void AC_PlayableBase::MoveForward(float Value)
{
	if (CanAction)
	{
		FVector FinalScale = GetActorForwardVector() * Value;
		AddMovementInput(FinalScale);
	}
}

void AC_PlayableBase::MoveRight(float Value)
{
	if (CanAction)
	{
		FVector FinalScale = GetActorRightVector() * Value;
		AddMovementInput(FinalScale);
	}
}

void AC_PlayableBase::RotatePitch(float Value)
{
	if (!IsDown)
	AddControllerPitchInput(Value * MouseSensitivity * GetWorld()->DeltaTimeSeconds);
}

void AC_PlayableBase::RotateYaw(float Value)
{
	if (!IsDown)
	AddControllerYawInput(Value * MouseSensitivity * GetWorld()->DeltaTimeSeconds);
}

void AC_PlayableBase::Attack()
{
	// ������ Ȥ�� �ڵ�󿡼� �˸��� �±� ���� �ʼ�
	if (ActorHasTag(TEXT("Range Type")))
		GunType_Fire();

	else if (ActorHasTag(TEXT("Melee Type")))
		MeleeType_ComboAttack();
}

void AC_PlayableBase::MeleeAttack()
{
	JustMeleeAttack();
}
