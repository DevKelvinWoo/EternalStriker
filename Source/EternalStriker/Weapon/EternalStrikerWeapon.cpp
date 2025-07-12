#include "EternalStrikerWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/DataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

#include "EternalStriker/Character/EternalStrikerMainCharacter.h"
#include "EternalStriker/Manager/EternalStrikerFXManager.h"
#include "EternalStriker/Enemy/EternalStrikerEnemy.h"

AEternalStrikerWeapon::AEternalStrikerWeapon()
{
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(RootComponent);;

	WeaponEquipCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponEquipCollision"));
	WeaponEquipCollision->SetupAttachment(RootComponent);

	WeaponEquipCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleOnWeaponEquipCollisionBeginOverlap);
	WeaponEquipCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::HandleOnWeaponEquipCollisionEndOverlap);
}

void AEternalStrikerWeapon::SetWeaponEquipCollision(ECollisionEnabled::Type InCollisionEnabled)
{
	check(WeaponEquipCollision);
	WeaponEquipCollision->SetCollisionEnabled(InCollisionEnabled);
}

void AEternalStrikerWeapon::SetWeaponReadyToAttack(const bool bReadyToAttack)
{
	bWeaponReadyToAttack = bReadyToAttack;
}

void AEternalStrikerWeapon::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeaponData();
}

void AEternalStrikerWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AttackByMultiLineTrace();
}

void AEternalStrikerWeapon::InitializeWeaponData()
{
	if (!ensureAlways(IsValid(WeaponData)))
	{
		return;
	}

	WeaponDataStruct = WeaponData->EternalWeaponDataStruct;
}

void AEternalStrikerWeapon::HandleOnWeaponEquipCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEternalStrikerMainCharacter* HitCharacter{ Cast<AEternalStrikerMainCharacter>(OtherActor) };
	if (!IsValid(HitCharacter))
	{
		return;
	}

	HitCharacter->SetEquipableWeapon(this);
}

void AEternalStrikerWeapon::HandleOnWeaponEquipCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEternalStrikerMainCharacter* HitCharacter{ Cast<AEternalStrikerMainCharacter>(OtherActor) };
	if (!IsValid(HitCharacter))
	{
		return;
	}

	HitCharacter->SetEquipableWeapon(nullptr);
}

void AEternalStrikerWeapon::AttackByMultiLineTrace()
{
	if (bWeaponReadyToAttack)
	{
		const FVector& LineTraceStart{ GetActorLocation() };
		const FVector& LineTraceEnd{ LineTraceStart + GetActorRightVector() * AttackLineTraceLength };
		const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1) };
		LineTraceIgnoreActors.Add(this);

		TArray<FHitResult> OutHits;
		UKismetSystemLibrary::LineTraceMultiForObjects(GetWorld(), LineTraceStart, LineTraceEnd, ObjectTypes, false, LineTraceIgnoreActors, EDrawDebugTrace::ForDuration, OutHits, true);

		const UGameInstance* GameInstance = GetGameInstance();
		check(GameInstance);

		const UEternalStrikerFXManager* FXManager{ GameInstance->GetSubsystem<UEternalStrikerFXManager>() };
		check(FXManager);

		for (const FHitResult& HitResult : OutHits)
		{
			AActor* HitActor{ HitResult.GetActor() };
			if (!IsValid(HitActor))
			{
				continue;
			}

			LineTraceIgnoreActors.AddUnique(HitActor);
			FXManager->SpawnFXAndFXSoundByData(WeaponDataStruct.WeaponHitNiagaraSystemData, TOptional<FVector>(HitResult.Location), nullptr);

			//@TODO : Character의 Stat이 구현되면 Stat에 무기의 AttackPower or MagicPower를 연산해서 데미지를 전달해야 함
			UGameplayStatics::ApplyDamage(HitActor, WeaponDataStruct.AttackPowerData, GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}
	else
	{
		LineTraceIgnoreActors.Empty();
	}
}
