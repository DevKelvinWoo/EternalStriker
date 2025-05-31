#include "EternalEquipComponent.h"

#include "EternalStriker/Character/EternalStrikerMainCharacter.h"
#include "EternalStriker//Weapon/EternalStrikerWeapon.h"

void UEternalEquipComponent::EquipWeapon() const
{
	if (!ensureAlways(EquipAnimMontage))
	{
		return;
	}

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
	if (!ensureAlways(IsValid(EquippedWeapon)))
	{
		return;
	}

	const AEternalStrikerMainCharacter* OwnerCharacter{ Cast<AEternalStrikerMainCharacter>(GetOwner()) };
	check(OwnerCharacter);

	USkeletalMeshComponent* OwnerCharacterMesh{ OwnerCharacter->GetMesh() };
	check(OwnerCharacterMesh);

	EquippedWeapon->AttachToComponent(OwnerCharacterMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
}
