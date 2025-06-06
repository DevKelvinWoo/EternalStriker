#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EternalStrikerWeapon.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class USphereComponent;
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

	void SetWeaponEquipCollision(ECollisionEnabled::Type InCollisionEnabled);
	void SetWeaponCollision(ECollisionEnabled::Type InCollisionEnabled);

protected:
	virtual void BeginPlay() override;

private:
	void InitializeWeaponData();

	UFUNCTION()
	void HandleOnWeaponEquipCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleOnWeaponEquipCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void HandleOnWeaponCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<UBoxComponent> WeaponCollision;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USphereComponent> WeaponEquipCollision;

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
