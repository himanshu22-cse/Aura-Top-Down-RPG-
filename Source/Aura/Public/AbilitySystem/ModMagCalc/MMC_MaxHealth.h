#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHealth.generated.h"

UCLASS()
class AURA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UMMC_MaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:

	/*
  So we have access to that gameplay effect spec, which means we have access to all the information inside

   of that and that's pretty great.

  Now mod mag Calcs can capture attributes.

  They have access to all the stuff in the effect spec.

   Yes, that's why they're so powerful.

  But they also have the ability to capture attributes and to capture attributes.

  We have to create a variable for the attribute we want to capture.

   So we're going to make a private section for that.

   It's FGameplay effect, attribute capture definition.

  Now, this is a gameplay effect attribute capture definition.

  It's a struct that defines what attribute we're going to capture.

  */

	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
