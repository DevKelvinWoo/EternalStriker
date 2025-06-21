#include "EternalStrikerSoundManager.h"

#include "Kismet/GameplayStatics.h"

#include "EternalStriker/EternalStrikerDefaultSettings.h"
#include "EternalStriker/Data/EternalSoundData.h"

void UEternalStrikerSoundManager::PlaySoundByName(const FName& InSoundName) const
{
	const UEternalSoundData* SoundData{ FindSoundData(InSoundName) };
	if (!IsValid(SoundData))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: SoundData is null"), __FUNCTION__);

		return;
	}

	USoundWave* SoundWave{ SoundData->SoundWaveData };
	const float VolumeMultiplier{ SoundData->VolumeMultiplier };
	const float PitchMultiplier{ SoundData->PitchMultiplier };
	const float StartTime{ SoundData->StartTime };

	UGameplayStatics::PlaySound2D(GetWorld(), SoundWave, VolumeMultiplier, PitchMultiplier, StartTime);
}

void UEternalStrikerSoundManager::PlaySoundByDataAsset(const UEternalSoundData* InSoundData) const
{
	if (!IsValid(InSoundData))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: SoundData is null"), __FUNCTION__);

		return;
	}

	USoundWave* SoundWave{ InSoundData->SoundWaveData };
	const float VolumeMultiplier{ InSoundData->VolumeMultiplier };
	const float PitchMultiplier{ InSoundData->PitchMultiplier };
	const float StartTime{ InSoundData->StartTime };

	UGameplayStatics::PlaySound2D(GetWorld(), SoundWave, VolumeMultiplier, PitchMultiplier, StartTime);
}

UEternalSoundData* UEternalStrikerSoundManager::FindSoundData(const FName& InSoundName) const
{
	const UEternalStrikerDefaultSettings* DefaultSettings{ GetDefault<UEternalStrikerDefaultSettings>() };
	check(DefaultSettings);

	if (DefaultSettings->SoundDataTable.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: SoundDataTable in DefaultSettings is null"), __FUNCTION__);

		return nullptr;
	}

	const UDataTable* LoadedSoundDataTable = DefaultSettings->SoundDataTable.LoadSynchronous();
	ensureAlways(LoadedSoundDataTable);

	const FEternalSoundDataTableRow* FXDataTableRow{ LoadedSoundDataTable->FindRow<FEternalSoundDataTableRow>(InSoundName, TEXT("")) };
	if (!FXDataTableRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: There is no Sound Data by %s"), __FUNCTION__, InSoundName);

		return nullptr;
	}

	UEternalSoundData* SoundDataAsset{ FXDataTableRow->SoundDataAsset };
	if (!IsValid(SoundDataAsset))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: FXDataAsset in FXDataTableRow is null"), __FUNCTION__);

		return nullptr;
	}

	return SoundDataAsset;
}
