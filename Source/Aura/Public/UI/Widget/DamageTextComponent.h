/*widget component  class capable of setting the damage text on its floating damage widget object.

The reason I wanted this Cplusplus class is simply for one thing, and that's that I'd like a

C plus plus function on this class so that if we create one of these from C plus plus, we can call

that function.

What we do in response to calling it I want to handle on the blueprint side.
*/
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"


UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool bBlockedHit, bool bCriticalHit);
};
