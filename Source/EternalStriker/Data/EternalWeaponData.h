#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EternalStriker/Weapon/EternalStrikerWeapon.h"
#include "EternalWeaponData.generated.h"

class UNiagaraSystem;
class USoundWave;

enum class EEternalWeaponCategory : uint8;

USTRUCT()
struct FEternalWeaponDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> WeaponAuraNiagaraSystemData;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsSwordWeapon"))
	TObjectPtr<UNiagaraSystem> WeaponHitNiagaraSystemData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> WeaponSwingSoundWaveData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> WeaponHitSoundWaveData;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "100"))
	int32 AttackPowerData{};

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "100"), meta = (EditCondition = "!bIsSwordWeapon"))
	int32 MagicPowerData{};

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "150"))
	int32 AdditionalSpeedData{};

	UPROPERTY(EditAnywhere)
	bool bIsSwordWeapon{ true };

	UPROPERTY(EditAnywhere)
	EEternalWeaponCategory WeaponCategoryData{ EEternalWeaponCategory::None };
};

UCLASS()
class ETERNALSTRIKER_API UEternalWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FEternalWeaponDataStruct EternalWeaponDataStruct;
};
