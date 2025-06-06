// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EternalKnightAnimInstance.generated.h"

UCLASS()
class ETERNALSTRIKER_API UEternalKnightAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AnimNotify_ResetComboCount();

	UFUNCTION()
	void AnimNotify_IncreaseComboCount();

	UFUNCTION()
	void AnimNotify_SetCanAttackState();

	UFUNCTION()
	void AnimNotify_SetCannotAttackState();

	UFUNCTION()
	void AnimNotify_EquipWeapon();

	UFUNCTION()
	void AnimNotify_EnableWeaponCollision();

	UFUNCTION()
	void AnimNotify_DisableWeaponCollision();
};
