#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled, FString, DescriptionString, FString, NextLevelDescriptionString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitForEquipSelectionSignature, const FGameplayTag&, AbilityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellGlobeReassignedSignature, const FGameplayTag&, AbilityTag); //For globe reaasigned

// for keep track of currently selected ability and it's status
struct FSelectedAbility
{
	FGameplayTag Ability = FGameplayTag();
	FGameplayTag Status = FGameplayTag();
};


UCLASS(BlueprintType, Blueprintable)
class AURA_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
		FOnPlayerStatChangedSignature SpellPointsChanged;

	UPROPERTY(BlueprintAssignable)
		FSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UPROPERTY(BlueprintAssignable)
		FWaitForEquipSelectionSignature WaitForEquipDelegate;

	UPROPERTY(BlueprintAssignable)
		FWaitForEquipSelectionSignature StopWaitingForEquipDelegate;

	UPROPERTY(BlueprintAssignable)
		FSpellGlobeReassignedSignature SpellGlobeReassignedDelegate;

	UFUNCTION(BlueprintCallable)
		void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
		void SpendPointButtonPressed();

	UFUNCTION(BlueprintCallable)
		void GlobeDeselect();

	UFUNCTION(BlueprintCallable)
		void EquipButtonPressed();

	/*
when we click the equip button, we're saving the selected slot or the input tag of our

currently selected ability if it's an equipped ability.

Otherwise it doesn't really have an input tag, right?

So that's important.

We'll keep track of that.

We also know that we're waiting for an equip selection.

So when our user actually makes a selection, we need to handle it.

When they click on one of the spell globes and the equipped spell row icon, we need to handle that.

So let's make a blueprint callable function for that.
*/

	UFUNCTION(BlueprintCallable)
		void SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType); // As we argument 2 tags one is in which slot(offensive or passive) and what type of ability tag is. 

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot);

private:

	static void ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton);

	// we set our selected ability every time we spell globe
	FSelectedAbility SelectedAbility = { FAuraGameplayTags::Get().Abilities_None,  FAuraGameplayTags::Get().Abilities_Status_Locked };
	int32 CurrentSpellPoints = 0;
	bool bWaitingForEquipSelection = false;

	FGameplayTag SelectedSlot; //selected slot is going to be set as soon as I click the equip button pressed,If our selected ability that we have selected, if the currently selected ability has the status of equipped.
};

