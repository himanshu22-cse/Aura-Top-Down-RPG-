#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"


UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations(); // we're going to know where we should spawn our little minions.

	UFUNCTION(BlueprintPure, Category = "Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();    

	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	int32 NumMinions = 5; 

// So we have a number of minions, so we need to know what class to spawn or class is if we're going to spawn multiple, even potentially different types of enemies or characters
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses; 

//minimum distance away that we should spawn our minions at.
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MinSpawnDistance = 50.f;

//maximum distance away that we should spawn our minions at.
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float MaxSpawnDistance = 250.f;

//spawned relatively in front of the shaman(angle of spread for spawning)
	UPROPERTY(EditDefaultsOnly, Category = "Summoning")
	float SpawnSpread = 90.f;

};
