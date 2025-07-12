#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EternalEquipComponent.generated.h"

class AEternalStrikerWeapon;

class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALSTRIKER_API UEternalEquipComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	AEternalStrikerWeapon* GetEquippedWeapon() const;
	void SetEquippedWeapon(AEternalStrikerWeapon* InWeapon);

	void EquipWeapon();

	void AttachWeaponToSocket() const;

	void SetEquipableWeapon(AEternalStrikerWeapon* InEquipableWeapon);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	TWeakObjectPtr<AEternalStrikerWeapon> EquipableWeapon;
	TWeakObjectPtr<AEternalStrikerWeapon> EquippedWeapon;
};
