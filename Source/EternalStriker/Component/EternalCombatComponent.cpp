#include "EternalCombatComponent.h"

#include "EternalStriker/Character/EternalStrikerMainCharacter.h"
#include "EternalStriker/Component/EternalEquipComponent.h"
#include "EternalStriker/Component/EternalCharacterStatComponent.h"
#include "EternalStriker/Weapon/EternalStrikerWeapon.h"
#include "EternalStriker/Manager/EternalStrikerSoundManager.h"

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

	//PlaySoundFX
	EquippedWeapon->PlayWeaponSwingSound();
	PlayCharacterCombatSound();

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

float UEternalCombatComponent::CalculateAttackPower() const
{
	const AEternalStrikerMainCharacter* OwnerCharacter{ Cast<AEternalStrikerMainCharacter>(GetOwner()) };
	check(OwnerCharacter);

	const UEternalEquipComponent* OwnerCharacterEquipComponent{ OwnerCharacter->GetEquipComponent() };
	check(OwnerCharacterEquipComponent);

	const UEternalCharacterStatComponent* OwnerCharacterStatComponent{ OwnerCharacter->GetCharacterStatComponent() };
	check(OwnerCharacterStatComponent);

	AEternalStrikerWeapon* EquippedWeapon{ OwnerCharacterEquipComponent->GetEquippedWeapon() };
	if (!IsValid(EquippedWeapon))
	{
		return 0.0f;
	}

	const float WeaponAttackPower{ EquippedWeapon->GetWeaponAttackPowerData() };
	const float CharacterAttackPowerStat{ OwnerCharacterStatComponent->GetAttackPower() };
	const float ResultAttackPower{ WeaponAttackPower + CharacterAttackPowerStat };

	return ResultAttackPower;
}

void UEternalCombatComponent::PlayCharacterCombatSound()
{
	UWorld* World{ GetWorld() };
	check(World);

	const UGameInstance* GameInstance{ World->GetGameInstance() };
	check(GameInstance);

	const UEternalStrikerSoundManager* FXManager{ GameInstance->GetSubsystem<UEternalStrikerSoundManager>() };
	check(FXManager);

	UEternalSoundData** CharacterCombatSoundData{ CombatCharacterSoundContainer.Find(CurrentComboCount) };
	FXManager->PlaySoundByDataAsset(*CharacterCombatSoundData);
}
