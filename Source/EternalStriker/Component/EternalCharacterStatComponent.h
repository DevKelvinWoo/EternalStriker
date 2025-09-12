#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EternalCharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ETERNALSTRIKER_API UEternalCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    // --- Getters ---
    float GetAttackPower() const { return AttackPower; }
    float GetMagicPower() const { return MagicPower; }
    float GetMaxHealth() const { return MaxHealth; }
    float GetCurrentHealth() const { return CurrentHealth; }
    float GetMaxMP() const { return MaxMP; }
    float GetCurrentMP() const { return CurrentMP; }
    float GetWalkSpeed() const { return WalkSpeed; }
    float GetRunSpeed() const { return RunSpeed; }
    float GetExp() const { return Exp; }
    float GetLevel() const { return Level; }
    float GetGold() const { return Gold; }
    float GetArmor() const { return Armor; }
    float GetMagicResist() const { return MagicResist; }
    float GetCriticalChance() const { return CriticalChance; }

    // --- Setters ---
    void SetAttackPower(float InAttackPower) { AttackPower = InAttackPower; }
    void SetMagicPower(float InMagicPower) { MagicPower = InMagicPower; }
    void SetMaxHealth(float InMaxHealth) { MaxHealth = InMaxHealth; }
    void SetCurrentHealth(float InCurrentHealth) { CurrentHealth = FMath::Clamp(InCurrentHealth, 0.0f, MaxHealth); }
    void SetMaxMP(float InMaxMP) { MaxMP = InMaxMP; }
    void SetCurrentMP(float InCurrentMP) { CurrentMP = FMath::Clamp(InCurrentMP, 0.0f, MaxMP); }
    void SetWalkSpeed(float InWalkSpeed) { WalkSpeed = InWalkSpeed; }
    void SetRunSpeed(float InRunSpeed) { RunSpeed = InRunSpeed; }
    void SetExp(float InExp) { Exp = InExp; }
    void SetLevel(float InLevel) { Level = InLevel; }
    void SetGold(float InGold) { Gold = InGold; }
    void SetArmor(float InArmor) { Armor = InArmor; }
    void SetMagicResist(float InMagicResist) { MagicResist = InMagicResist; }
    void SetCriticalChance(float InCriticalChance) { CriticalChance = InCriticalChance; }

private:
	float AttackPower{ 50.0 };
	float MagicPower{ 50.0 };
	float MaxHealth{ 100.0 };
	float CurrentHealth{ 100.0 };
	float MaxMP{ 100.0 };
	float CurrentMP{ 100.0 };
	float WalkSpeed{ 550.0 };
	float RunSpeed{ 950.0 };
	float Exp{ 0.0 };
	float Level{ 1.0 };
	float Gold{ 0.0 };
	float Armor{ 0.0 };
	float MagicResist{ 0.0 };
	float CriticalChance{ 0.0 };
};
