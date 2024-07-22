#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly)
		const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FGameplayTag InputTag = FGameplayTag();
};

UCLASS()
class AURA_API UAuraInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	// Array for storing input for abilities
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FAuraInputAction> AbilityInputActions;
};
