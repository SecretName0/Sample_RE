// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PMC = CreateDefaultSubobject<UProjectileMovementComponent>
		(TEXT("Projectile Movement Component"));

	PMC->MaxSpeed = ProjectileMaxSpeed; // 최대 속도
	PMC->InitialSpeed = ProjectileInitialSpeed; // 초기 발사 속도
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	HitTarget = Cast<ACharacterBase>(OtherActor);
	//UE_LOG(LogTemp, Display, TEXT("HitTarget: %s"),
		//*HitTarget->GetName());

	if (HitTarget)
	{
		if (HitTarget->ActorHasTag("Player") || HitTarget->ActorHasTag("Enemy"))
		{
			ACharacterBase* ProjectileOwner = Cast<ACharacterBase>(GetOwner());

			if (ProjectileOwner)
			{
				//UE_LOG(LogTemp, Display, TEXT("%s"), 
					//*ProjectileOwner->GetActorNameOrLabel());

				AController* OwnerCont = ProjectileOwner->GetInstigatorController();

				if (ProjectileOwner->ActorHasTag("Player"))
				{
					AACO_PlayerControllerBase* AttackerController = Cast<AACO_PlayerControllerBase>
						(OwnerCont);
					// 만약 플레이어가 투사체를 생성하지 않고
					// 아군 AI에 의한 투사체 오폭이 존재할 경우
					// 컨트롤러를 또 바꾸면 됨

					if (AttackerController)
					{
						//UE_LOG(LogTemp, Display, TEXT("%s"),
							//*AttackerController->GetName());

						UGameplayStatics::ApplyDamage(HitTarget, ProjectileOwner->ProjectileStrength,
							AttackerController, this, nullptr);
					}
				}

				else if(ProjectileOwner->ActorHasTag("Enemy"))
				{
					AAIC_EnemyControllerBase* AttackerController = Cast<AAIC_EnemyControllerBase>
						(OwnerCont);
				}
				
				
			}
		}
	}

	Destroy();
}

void AProjectileBase::GetTargetData(AActor* Actor)
{
	
}
