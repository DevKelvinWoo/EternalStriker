#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EternalFXData.generated.h"

class UNiagaraSystem;
class USoundWave;

USTRUCT()
struct FEternalFXDataStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName FXNameData{ NAME_None };

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> FXNiagaraSystemData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundWave> FXSoundWaveData;

	UPROPERTY(EditAnywhere)
	FVector FXScaleData{ 1.0f, 1.0f, 1.0f };

	UPROPERTY(EditAnywhere)
	FRotator FXRotationData{ 0.0f, 0.0f, 0.0f };

	UPROPERTY(EditAnywhere)
	FName FXSocketNameData{ NAME_None };

	UPROPERTY(EditAnywhere)
	bool bIsLooping{ false };
};

UCLASS()
class ETERNALSTRIKER_API UEternalFXData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FEternalFXDataStruct EternalFXDataStruct;
};
