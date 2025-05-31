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

	//현재 장착중인 무기 포인터
	//장착 시전 시 재생할 AnimMontage

public:
	const AEternalStrikerWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	void SetEquippedWeapon(AEternalStrikerWeapon* InWeapon) { EquippedWeapon = InWeapon; };

	void EquipWeapon() const;

	void AttachWeaponToSocket() const;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	UPROPERTY(Transient)
	TObjectPtr<AEternalStrikerWeapon> EquippedWeapon;
};
