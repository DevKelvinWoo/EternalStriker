#include "EternalCombatComponent.h"

#include "EternalStriker/Character/EternalStrikerMainCharacter.h"

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
		CurrentComboCount = 0;
	}
}

void UEternalCombatComponent::ResetCurrentComboCount()
{
	CurrentComboCount = 0;
}
