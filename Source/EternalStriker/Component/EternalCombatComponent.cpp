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

	AEternalStrikerMainCharacter* OwnerCharacter{ Cast<AEternalStrikerMainCharacter>(GetOwner()) };
	check(OwnerCharacter);

	USkeletalMeshComponent* OwnerCharacterMesh{ OwnerCharacter->GetMesh() };
	check(OwnerCharacterMesh);

	UAnimInstance* OwnerCharacterAnimInstance{ OwnerCharacterMesh->GetAnimInstance() };
	check(OwnerCharacterAnimInstance);

	const FName* MontageSectionNameToJump{ ComboMontageSectionNameContainer.Find(CurrentComboCount) };

	OwnerCharacterAnimInstance->Montage_Play(CombatMontage, 1.f);
	OwnerCharacterAnimInstance->Montage_JumpToSection(*MontageSectionNameToJump, CombatMontage);
}

void UEternalCombatComponent::IncreaseCurrentComboCount()
{
	UE_LOG(LogTemp, Warning, TEXT("Increase"));
	++CurrentComboCount;
}

void UEternalCombatComponent::ResetCurrentComboCount()
{
	UE_LOG(LogTemp, Warning, TEXT("Reset"));
	CurrentComboCount = 0;
}
