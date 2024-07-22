#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TargetDataUnderMouse", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
		static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
		FMouseTargetDataSignature ValidData;

private:

	virtual void Activate() override;

	/*
	And we found that just getting our mouse cursor data and broadcasting is not going to work.

	As if this is not a locally controlled player, then this cursor hit will not have valid data.

	So we need a function that we can use to send data to the server and we should call this function if

	we're locally controlled.

	 So I'm going to make a function on target data under mouse.

	This can be private and we'll call this void function send mouse cursor data.
	*/

	void SendMouseCursorData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
