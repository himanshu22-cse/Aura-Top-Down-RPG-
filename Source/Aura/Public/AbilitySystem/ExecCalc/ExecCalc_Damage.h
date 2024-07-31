#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"


UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UExecCalc_Damage();

	//  "FGameplayEffectCustomExecutionParameters" ->custom execution calculations, allowing you to define complex logic that goes beyond simple attribute modifications.
	void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		const FGameplayEffectSpec& Spec,
		FAggregatorEvaluateParameters EvaluationParameters,
		const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const;

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

};
