#include "EternalStrikerFXManager.h"

#include "Engine/DataTable.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"

#include "EternalStriker/EternalStrikerDefaultSettings.h"
#include "EternalStriker/Data/EternalFXData.h"

void UEternalStrikerFXManager::SpawnFXByName(const FName& InFXName, TOptional<FVector> OptionalFXLocation, const ACharacter* InTargetCharacter)
{
	UEternalFXData* FXData{ FindFXData(InFXName) };
	if (!IsValid(FXData))
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs: FXData is null"), __FUNCTION__);

		return;
	}

	FEternalFXDataStruct FXDataStruct{ FXData->EternalFXDataStruct };

	FVector FXLocation{};
	if (OptionalFXLocation.IsSet())
	{
		FXLocation = OptionalFXLocation.GetValue();
	}
	
	if (IsValid(InTargetCharacter))
	{
		FXLocation = InTargetCharacter->GetMesh()->GetSocketLocation(FXDataStruct.FXSocketNameData);
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

	UDataTable* LoadedFXDataTable = DefaultSettings->FXDataTable.LoadSynchronous();
	ensureAlways(LoadedFXDataTable);

	FEternalFXDataTableRow* FXDataTableRow{ LoadedFXDataTable->FindRow<FEternalFXDataTableRow>(InFXName, TEXT("")) };
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
