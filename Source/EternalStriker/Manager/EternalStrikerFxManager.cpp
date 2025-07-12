#include "EternalStrikerFXManager.h"

#include "Engine/DataTable.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "EternalStriker/EternalStrikerDefaultSettings.h"
#include "EternalStriker/Data/EternalFXData.h"
#include "EternalStriker/Data/EternalSoundData.h"
#include "EternalStriker/Manager/EternalStrikerSoundManager.h"

void UEternalStrikerFXManager::SpawnFXAndFXSoundByName(const FName& InFXName, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter) const
{
	const UEternalFXData* FXData{ FindFXData(InFXName) };
	if (!IsValid(FXData))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: FXData is null"), __FUNCTION__);

		return;
	}

	const FEternalFXDataStruct& FXDataStruct{ FXData->EternalFXDataStruct };

	FVector FXLocation{};
	if (OptionalFXLocation.IsSet())
	{
		FXLocation = OptionalFXLocation.GetValue();
	}
	
	UNiagaraSystem* FXNiagaraSystemData{ FXDataStruct.FXNiagaraSystemData };
	const UEternalSoundData* SoundData{ FXDataStruct.SoundData };
	const FVector& FXScaleData{ FXDataStruct.FXScaleData };
	const FRotator& FXRotatorData{ FXDataStruct.FXRotationData };
	const FName& FXSocketNameData{ FXDataStruct.FXSocketNameData };
	const bool FXLoopingData{ FXDataStruct.bIsLooping };

	if (IsValid(InTargetCharacter))
	{
		const USkeletalMeshComponent* SkeletalMesh{ InTargetCharacter->GetMesh() };
		check(SkeletalMesh);

		FXLocation = SkeletalMesh->GetSocketLocation(FXSocketNameData);
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		FXNiagaraSystemData,
		FXLocation,
		FXRotatorData,
		FXScaleData,
		true,
		true
	);

	if (IsValid(SoundData))
	{
		const UGameInstance* GameInstance = GetGameInstance();
		check(GameInstance);

		const UEternalStrikerSoundManager* SoundManager{ GameInstance->GetSubsystem<UEternalStrikerSoundManager>() };
		check(SoundManager);

		SoundManager->PlaySoundByDataAsset(SoundData);
	}
}

void UEternalStrikerFXManager::SpawnFXAndFXSoundByData(const UEternalFXData* InFXData, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter) const
{
	if (!IsValid(InFXData))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: InFXData is null"), __FUNCTION__);

		return;

	}

	FVector FXLocation{};
	if (OptionalFXLocation.IsSet())
	{
		FXLocation = OptionalFXLocation.GetValue();
	}

	const FEternalFXDataStruct& FXDataStruct{ InFXData->EternalFXDataStruct };

	UNiagaraSystem* FXNiagaraSystemData{ FXDataStruct.FXNiagaraSystemData };
	const UEternalSoundData* SoundData{ FXDataStruct.SoundData };
	const FVector& FXScaleData{ FXDataStruct.FXScaleData };
	const FRotator& FXRotatorData{ FXDataStruct.FXRotationData };
	const FName& FXSocketNameData{ FXDataStruct.FXSocketNameData };
	const bool FXLoopingData{ FXDataStruct.bIsLooping };

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		FXNiagaraSystemData,
		FXLocation,
		FXRotatorData,
		FXScaleData,
		true,
		true
	);

	if (IsValid(SoundData))
	{
		const UGameInstance* GameInstance = GetGameInstance();
		check(GameInstance);

		const UEternalStrikerSoundManager* SoundManager{ GameInstance->GetSubsystem<UEternalStrikerSoundManager>() };
		check(SoundManager);

		SoundManager->PlaySoundByDataAsset(SoundData);
	}
}

UEternalFXData* UEternalStrikerFXManager::FindFXData(const FName& InFXName) const
{
	const UEternalStrikerDefaultSettings* DefaultSettings{ GetDefault<UEternalStrikerDefaultSettings>() };
	check(DefaultSettings);

	if (DefaultSettings->FXDataTable.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: FXDataTable in DefaultSettings is null"), __FUNCTION__);

		return nullptr;
	}

	const UDataTable* LoadedFXDataTable = DefaultSettings->FXDataTable.LoadSynchronous();
	ensureAlways(LoadedFXDataTable);

	const FEternalFXDataTableRow* FXDataTableRow{ LoadedFXDataTable->FindRow<FEternalFXDataTableRow>(InFXName, TEXT("")) };
	if (!FXDataTableRow)
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: There is no FX Data by %s"), __FUNCTION__, InFXName);

		return nullptr;
	}

	UEternalFXData* FXDataAsset{ FXDataTableRow->FXDataAsset };
	if (!IsValid(FXDataAsset))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: FXDataAsset in FXDataTableRow is null"), __FUNCTION__);

		return nullptr;
	}

	return FXDataAsset;
}
