#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EternalStriker/Data/EternalFXData.h"
#include "EternalStrikerFXManager.generated.h"

class UEternalFXData;

UCLASS()
class ETERNALSTRIKER_API UEternalStrikerFXManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SpawnFXAndSoundByName(const FName& InFXName, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter) const;

private:
	UEternalFXData* FindFXData(const FName& InFXName) const;
};
