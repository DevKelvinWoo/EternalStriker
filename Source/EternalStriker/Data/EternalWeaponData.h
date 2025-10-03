#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EternalWeaponData.generated.h"

class UEternalFXData;
class UEternalSoundData;

UENUM()
enum class EEternalWeaponCategory : uint8
{
	None,
	Sword,
	Staff
};

USTRUCT()
struct FEternalWeaponDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEternalFXData> WeaponAuraNiagaraSystemData;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bIsSwordWeapon"))
	TObjectPtr<UEternalFXData> WeaponHitNiagaraSystemData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEternalSoundData> WeaponSwingSoundWaveData;

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
	FEternalWeaponDataStruct EternalWeaponDataStruct{};
};
