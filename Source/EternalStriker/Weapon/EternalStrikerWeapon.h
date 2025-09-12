#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EternalStriker/Data/EternalWeaponData.h"
#include "EternalStrikerWeapon.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class USphereComponent;
class UCameraShakeBase;

class AEternalStrikerMainCharacter;

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerWeapon : public AActor
{
	GENERATED_BODY()

public:
	AEternalStrikerWeapon();

	void SetWeaponEquipCollision(ECollisionEnabled::Type InCollisionEnabled);
	void SetWeaponReadyToAttack(const bool bReadyToAttack);

	void PlayWeaponSwingSound();

	float GetWeaponAttackPowerData() const { return WeaponDataStruct.AttackPowerData; }

	void SetOwnerCharacter(AEternalStrikerMainCharacter* InOwnerCharacter);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	void InitializeWeaponData();

	UFUNCTION()
	void HandleOnWeaponEquipCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void HandleOnWeaponEquipCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void AttackByMultiLineTrace();

	void PlayHitImpactEffects(const FVector& HitLocation);

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USphereComponent> WeaponEquipCollision;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<UEternalWeaponData> WeaponData;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TSubclassOf<UCameraShakeBase> WeaponCameraShakeClass;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	float AttackLineTraceLength{ 0.f };

	TWeakObjectPtr<AEternalStrikerMainCharacter> OwnerCharacterWeak;

	FEternalWeaponDataStruct WeaponDataStruct;

	TArray<AActor*> LineTraceIgnoreActors{};

	bool bWeaponReadyToAttack{ false };

	FTimerHandle HitStopTimerHandle;
};
