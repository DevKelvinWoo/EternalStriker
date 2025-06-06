#include "EternalEquipComponent.h"

#include "EternalStriker/Character/EternalStrikerMainCharacter.h"
#include "EternalStriker//Weapon/EternalStrikerWeapon.h"

AEternalStrikerWeapon* UEternalEquipComponent::GetEquippedWeapon() const
{
	if (!EquippedWeapon.IsValid())
	{
		return nullptr;
	}

	return EquippedWeapon.Get();
}

void UEternalEquipComponent::SetEquippedWeapon(AEternalStrikerWeapon* InWeapon)
{
	if (!ensureAlways(IsValid(InWeapon)))
	{
		return;
	}

	EquippedWeapon = MakeWeakObjectPtr(InWeapon);
}

void UEternalEquipComponent::EquipWeapon()
{
	if (!ensureAlways(EquipAnimMontage))
	{
		return;
	}

	if (!EquipableWeapon.IsValid())
	{
		return;
	}

	if (EquippedWeapon.IsValid())
	{
		EquippedWeapon->Destroy();
		EquippedWeapon.Reset();
	}

	EquippedWeapon = EquipableWeapon;
	EquipableWeapon.Reset();

	EquippedWeapon->SetWeaponEquipCollision(ECollisionEnabled::NoCollision);

	const AEternalStrikerMainCharacter* OwnerCharacter{ Cast<AEternalStrikerMainCharacter>(GetOwner()) };
	check(OwnerCharacter);

	const USkeletalMeshComponent* OwnerCharacterMesh{ OwnerCharacter->GetMesh() };
	check(OwnerCharacterMesh);

	UAnimInstance* OwnerCharacterAnimInstance{ OwnerCharacterMesh->GetAnimInstance() };
	check(OwnerCharacterAnimInstance);

	check(EquipAnimMontage);
	OwnerCharacterAnimInstance->Montage_Play(EquipAnimMontage, 1.f);
}

void UEternalEquipComponent::AttachWeaponToSocket() const
{
	if (!EquippedWeapon.IsValid())
	{
		return;
	}

	const AEternalStrikerMainCharacter* OwnerCharacter{ Cast<AEternalStrikerMainCharacter>(GetOwner()) };
	check(OwnerCharacter);

	USkeletalMeshComponent* OwnerCharacterMesh{ OwnerCharacter->GetMesh() };
	check(OwnerCharacterMesh);

	AEternalStrikerWeapon* WeaponToAttach{ EquippedWeapon.Get() };
	const FTransform& InitialWeaponTransform{ FRotator::ZeroRotator, FVector::ZeroVector, FVector::OneVector };

	WeaponToAttach->SetActorTransform(InitialWeaponTransform);

	const FAttachmentTransformRules WeaponAttachmentRules(EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
	const FName& WeaponSocketName{ TEXT("WeaponSocket") };
	WeaponToAttach->AttachToComponent(OwnerCharacterMesh, WeaponAttachmentRules, WeaponSocketName);
}

void UEternalEquipComponent::SetEquipableWeapon(AEternalStrikerWeapon* InEquipableWeapon)
{
	EquipableWeapon = MakeWeakObjectPtr(InEquipableWeapon);
}
