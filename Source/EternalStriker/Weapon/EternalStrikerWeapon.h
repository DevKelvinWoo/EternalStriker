#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EternalStriker/Data/EternalWeaponData.h"
#include "EternalStrikerWeapon.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class USphereComponent;

UCLASS()
class ETERNALSTRIKER_API AEternalStrikerWeapon : public AActor
{
	GENERATED_BODY()

public:
	AEternalStrikerWeapon();

	void SetWeaponEquipCollision(ECollisionEnabled::Type InCollisionEnabled);
	void SetWeaponReadyToAttack(const bool bReadyToAttack);

	void PlayWeaponSwingSound();

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

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<USphereComponent> WeaponEquipCollision;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	TObjectPtr<UEternalWeaponData> WeaponData;

	FEternalWeaponDataStruct WeaponDataStruct;

	UPROPERTY(EditAnywhere, meta = (PrivateAccessAllow = "true"))
	float AttackLineTraceLength{ 0.f };

	TArray<AActor*> LineTraceIgnoreActors;

	bool bWeaponReadyToAttack{ false };
};
