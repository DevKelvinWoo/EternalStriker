#include "EternalStrikerWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/DataAsset.h"

#include "EternalStriker/Data/EternalWeaponData.h"

AEternalStrikerWeapon::AEternalStrikerWeapon()
{
	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	WeaponSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMesh"));
	WeaponSkeletalMesh->SetupAttachment(RootComponent);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetupAttachment(WeaponSkeletalMesh);
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
