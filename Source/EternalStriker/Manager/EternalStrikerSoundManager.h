#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EternalStrikerSoundManager.generated.h"

class UEternalSoundData;

UCLASS()
class ETERNALSTRIKER_API UEternalStrikerSoundManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void PlaySoundByName(const FName& InSoundName) const;
	void PlaySoundByDataAsset(const UEternalSoundData* InSoundData) const;

private:
	UEternalSoundData* FindSoundData(const FName& InSoundName) const;
};
