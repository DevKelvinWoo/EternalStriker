// Fill out your copyright notice in the Description page of Project Settings.


#include "EternalKnightAnimInstance.h"

#include "EternalStriker/Character/EternalStrikerKnight.h"
#include "EternalStriker/Component/EternalCombatComponent.h"
#include "EternalStriker/Component/EternalEquipComponent.h"
#include "EternalStriker/Weapon/EternalStrikerWeapon.h"

void UEternalKnightAnimInstance::AnimNotify_ResetComboCount()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->ResetCurrentComboCount();
}

void UEternalKnightAnimInstance::AnimNotify_IncreaseComboCount()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->IncreaseCurrentComboCount();
}

void UEternalKnightAnimInstance::AnimNotify_SetCanAttackState()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->SetCanAttackState(true);
}

void UEternalKnightAnimInstance::AnimNotify_SetCannotAttackState()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalCombatComponent* OwnerKnightCombatComponent{ OwnerKnight->GetCombatComponent() };
	check(OwnerKnightCombatComponent);

	OwnerKnightCombatComponent->SetCanAttackState(false);
}

void UEternalKnightAnimInstance::AnimNotify_EquipWeapon()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	const UEternalEquipComponent* OwnerKnightEquipComponent{ OwnerKnight->GetEquipComponent() };
	check(OwnerKnightEquipComponent);

	OwnerKnightEquipComponent->AttachWeaponToSocket();
}

void UEternalKnightAnimInstance::AnimNotify_EnableWeaponCollision()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalEquipComponent* OwnerKnightEquipComponent{ OwnerKnight->GetEquipComponent() };
	check(OwnerKnightEquipComponent);

	AEternalStrikerWeapon* EquippedWeapon{ OwnerKnightEquipComponent->GetEquippedWeapon() };
	check(EquippedWeapon);

	EquippedWeapon->SetWeaponCollision(ECollisionEnabled::QueryAndPhysics);
}

void UEternalKnightAnimInstance::AnimNotify_DisableWeaponCollision()
{
	const AEternalStrikerKnight* OwnerKnight{ Cast<AEternalStrikerKnight>(TryGetPawnOwner()) };
	check(OwnerKnight);

	UEternalEquipComponent* OwnerKnightEquipComponent{ OwnerKnight->GetEquipComponent() };
	check(OwnerKnightEquipComponent);

	AEternalStrikerWeapon* EquippedWeapon{ OwnerKnightEquipComponent->GetEquippedWeapon() };
	check(EquippedWeapon);

	EquippedWeapon->SetWeaponCollision(ECollisionEnabled::NoCollision);
}
