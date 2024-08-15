
#include "AbilitySystem/Abilities/AuraFireBlast.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		// Title
		"<Title>FIRE BLAST</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Number of Fire Balls
		"<Default>Launches %d </>"
		"<Default>fire balls in all directions, each coming back and </>"
		"<Default>exploding upon return, causing </>"

		// Damage
		"<Damage>%d</><Default> radial fire damage with"
		" a chance to burn</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		NumFireBalls,
		ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL:</>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// ManaCost
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Number of Fire Balls
		"<Default>Launches %d </>"
		"<Default>fire balls in all directions, each coming back and </>"
		"<Default>exploding upon return, causing </>"

		// Damage
		"<Damage>%d</><Default> radial fire damage with"
		" a chance to burn</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		NumFireBalls,
		ScaledDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());

//CurrentActorInfo()-> is often used within the context of the Gameplay Ability System (GAS). It typically refers to a pointer of type FGameplayAbilityActorInfo, which contains essential information about the actor currently executing an ability.
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(
			FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();
		FireBall->SetOwner(GetAvatarActorFromActorInfo()); //if we have this set, the owner on all actors is replicated,So the fireball is going to know on the client who its owner is.

		FireBall->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner(GetAvatarActorFromActorInfo());  // So That our aura can get affected ...(in BP_Fireball).

		FireBalls.Add(FireBall);

		FireBall->FinishSpawning(SpawnTransform);
	}

	return FireBalls;
}
