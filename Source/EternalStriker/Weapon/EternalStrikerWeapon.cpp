#include "EternalStrikerWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/DataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

#include "EternalStriker/Data/EternalWeaponData.h"
#include "EternalStriker/Character/EternalStrikerMainCharacter.h"

AEternalStrikerWeapon::AEternalStrikerWeapon()
{
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(RootComponent);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(WeaponSkeletalMesh);
	WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleOnWeaponCollisionBeginOverlap);

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

void AEternalStrikerWeapon::SetWeaponCollision(ECollisionEnabled::Type InCollisionEnabled)
{
	check(WeaponCollision);
	WeaponCollision->SetCollisionEnabled(InCollisionEnabled);
}

void AEternalStrikerWeapon::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeaponData();
}

void AEternalStrikerWeapon::InitializeWeaponData()
{
	if (!ensureAlways(IsValid(WeaponData)))
	{
		return;
	}

	const FEternalWeaponDataStruct& WeaponDataStruct{ WeaponData->EternalWeaponDataStruct };

	AttackPower = WeaponDataStruct.AttackPowerData;
	MagicPower = WeaponDataStruct.MagicPowerData;
	AdditionalSpeed = WeaponDataStruct.AdditionalSpeedData;

	WeaponAuraNiagara = WeaponDataStruct.WeaponAuraNiagaraSystemData;
	WeaponHitNiagara = WeaponDataStruct.WeaponHitNiagaraSystemData;

	WeaponSwingSound = WeaponDataStruct.WeaponSwingSoundWaveData;
	WeaponHitSound = WeaponDataStruct.WeaponHitSoundWaveData;

	WeaponCategory = WeaponDataStruct.WeaponCategoryData;
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

void AEternalStrikerWeapon::HandleOnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	//@TODO : Character의 Stat이 구현되면 Stat에 AttackPower or MagicPower를 곱해서 데미지를 전달해야 함
	UGameplayStatics::ApplyDamage(OtherActor, AttackPower, GetInstigatorController(), this, UDamageType::StaticClass());
}
