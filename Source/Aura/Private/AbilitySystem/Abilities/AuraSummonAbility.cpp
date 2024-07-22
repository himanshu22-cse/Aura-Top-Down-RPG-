
#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;  // Angle b/w each of vector to spawn mininons


	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;

	//Starting at  "LeftOfSpread" and continue rotating by "DeltaSpread" each iteration of the for loop
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance); // for random place spawn of enemy

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 400.f), ChosenSpawnLocation - FVector(0.f, 0.f, 400.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0, MinionClasses.Num() - 1);
	return MinionClasses[Selection];
}
