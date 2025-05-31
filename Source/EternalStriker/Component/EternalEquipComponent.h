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

	//���� �������� ���� ������
	//���� ���� �� ����� AnimMontage

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
