#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EternalStrikerDefaultSettings.generated.h"

class UDataTable;

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "EternalStriker Default"))
class ETERNALSTRIKER_API UEternalStrikerDefaultSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(config, EditAnywhere)
	TSoftObjectPtr<UDataTable> FXDataTable;

	UPROPERTY(config, EditAnywhere)
	TSoftObjectPtr<UDataTable> SoundDataTable;
};
