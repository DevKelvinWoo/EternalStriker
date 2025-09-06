#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EternalSoundData.generated.h"

USTRUCT()
struct FEternalSoundDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> SoundWaveData;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float VolumeMultiplier{ 1.f };

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float PitchMultiplier{ 1.f };

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0"))
	float StartTime{ 0.f };
};

UCLASS()
class ETERNALSTRIKER_API UEternalSoundData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FEternalSoundDataStruct EternalSoundDataStruct;
};

USTRUCT()
struct FEternalSoundDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEternalSoundData> SoundDataAsset;
};
