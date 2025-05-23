#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EternalStrikerWeapon.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class UNiagaraSystem;
class USoundWave;

class UEternalWeaponData;

UENUM()
enum class EEternalWeaponCategory : uint8
{
	None,
	Sword,
	Staff
};

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerWeapon : public AActor
{
	GENERATED_BODY()

public:
	AEternalStrikerWeapon();

protected:
	virtual void BeginPlay() override;

private:
	void InitializeWeaponData();

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<UBoxComponent> WeaponCollision;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<UEternalWeaponData> WeaponData;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> WeaponAuraNiagara;

	UPROPERTY(Transient)
	TObjectPtr<UNiagaraSystem> WeaponHitNiagara;

	UPROPERTY(Transient)
	TObjectPtr<USoundWave> WeaponSwingSound;

	UPROPERTY(Transient)
	TObjectPtr<USoundWave> WeaponHitSound;

	int32 AttackPower{};
	int32 MagicPower{};
	int32 AdditionalSpeed{};

	EEternalWeaponCategory WeaponCategory{ EEternalWeaponCategory::None };
};
