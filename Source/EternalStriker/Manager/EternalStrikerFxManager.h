#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EternalStriker/Data/EternalFXData.h"
#include "EternalStrikerFXManager.generated.h"

class UNiagaraSystem;

class UEternalFXData;
class UEternalSoundData;

UCLASS()
class ETERNALSTRIKER_API UEternalStrikerFXManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SpawnFXAndFXSoundByName(const FName& InFXName, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter) const;
	void SpawnFXAndFXSoundByData(const UEternalFXData* InFXData, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter) const;

private:
	UEternalFXData* FindFXData(const FName& InFXName) const;
};
