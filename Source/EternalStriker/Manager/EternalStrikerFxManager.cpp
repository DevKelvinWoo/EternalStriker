#include "EternalStrikerFXManager.h"

#include "Engine/DataTable.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

#include "EternalStriker/EternalStrikerDefaultSettings.h"
#include "EternalStriker/Data/EternalFXData.h"

void UEternalStrikerFXManager::SpawnFXAndSoundByName(const FName& InFXName, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter) const
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
	
	if (IsValid(InTargetCharacter))
	{
		const USkeletalMeshComponent* SkeletalMesh{ InTargetCharacter->GetMesh() };
		check(SkeletalMesh);

		FXLocation = SkeletalMesh->GetSocketLocation(FXDataStruct.FXSocketNameData);
	}
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		FXDataStruct.FXNiagaraSystemData,
		FXLocation,
		FXDataStruct.FXRotationData,
		FXDataStruct.FXScaleData,
		true,
		true
	);

	//SoundManager구현 후 여기서 호출
	UGameplayStatics::PlaySound2D(GetWorld(), FXDataStruct.FXSoundWaveData);
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
