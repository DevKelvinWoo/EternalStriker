// Fill out your copyright notice in the Description page of Project Settings.


#include "EternalKnightAnimInstance.h"

#include "EternalStriker/Character/EternalStrikerKnight.h"
#include "EternalStriker/Component/EternalCombatComponent.h"
#include "EternalStriker/Component/EternalEquipComponent.h"

void UEternalKnightAnimInstance::AnimNotify_ResetComboCount()
{
	AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->ResetCurrentComboCount();
}

void UEternalKnightAnimInstance::AnimNotify_IncreaseComboCount()
{
	AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->IncreaseCurrentComboCount();
}

void UEternalKnightAnimInstance::AnimNotify_SetCanAttackState()
{
	AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->SetCanAttackState(true);
}

void UEternalKnightAnimInstance::AnimNotify_SetCannotAttackState()
{
	AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->SetCanAttackState(false);
}

void UEternalKnightAnimInstance::AnimNotify_EquipWeapon()
{
	AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalEquipComponent* OwnerKnightEquipComponent{ OwnerKnight->GetEquipComponent() };
	check(OwnerKnightEquipComponent);

	OwnerKnightEquipComponent->AttachWeaponToSocket();
}
