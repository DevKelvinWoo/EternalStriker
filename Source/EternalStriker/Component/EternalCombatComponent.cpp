#include "EternalCombatComponent.h"

#include "EternalStriker/Character/EternalStrikerMainCharacter.h"
#include "EternalStriker/Component/EternalEquipComponent.h"
#include "EternalStriker/Weapon/EternalStrikerWeapon.h"

void UEternalCombatComponent::AttackBasic()
{
	if (!ensureAlways(CombatMontage))
	{
		return;
	}

	if (!bCanAttack)
	{
		return;
	}

	const AEternalStrikerMainCharacter* OwnerCharacter{ Cast<AEternalStrikerMainCharacter>(GetOwner()) };
	check(OwnerCharacter);

	const UEternalEquipComponent* OwnerCharacterEquipComponent{ OwnerCharacter->GetEquipComponent() };
	check(OwnerCharacterEquipComponent);

	AEternalStrikerWeapon* EquippedWeapon{ OwnerCharacterEquipComponent->GetEquippedWeapon() };
	if (!IsValid(EquippedWeapon))
	{
		return;
	}

	const USkeletalMeshComponent* OwnerCharacterMesh{ OwnerCharacter->GetMesh() };
	check(OwnerCharacterMesh);

	UAnimInstance* OwnerCharacterAnimInstance{ OwnerCharacterMesh->GetAnimInstance() };
	check(OwnerCharacterAnimInstance);

	const FName* MontageSectionNameToJump{ ComboMontageSectionNameContainer.Find(CurrentComboCount) };

	OwnerCharacterAnimInstance->Montage_Play(CombatMontage, 1.f);
	OwnerCharacterAnimInstance->Montage_JumpToSection(*MontageSectionNameToJump, CombatMontage);
}

void UEternalCombatComponent::IncreaseCurrentComboCount()
{
	++CurrentComboCount;

	if (CurrentComboCount > FullComboCount)
	{
		ResetCurrentComboCount();
	}
}

void UEternalCombatComponent::ResetCurrentComboCount()
{
	CurrentComboCount = 0;
}
