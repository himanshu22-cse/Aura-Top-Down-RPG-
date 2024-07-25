#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FAuraAbilityInfo;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase // inherit from FTableRowBase struct and that's the base class for row structure for data tables.
{
	GENERATED_BODY()

	//Now this row structure that we'll use in our data asset is going to obviously need a gameplay tag.  
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag(); // this is going to be specifically for messages to display to the screen,we'll make sure these are all initialized, So I'll initialize it to an empty gameplay tag, So there's the tag.

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();  //And in the realm of widgets, when we display text to the user in the form of a widget, we use text that's user facing text that we show in widgets.

	/*
			So for any given gameplay tag, there will be a widget that we can create and add to the viewport whenever

			we receive this tag in the form of a gameplay effect.

			So I'm going to make a subclass of and it's going to be of type you or a user widget because we're going

			to only use aura user widgets for this.
			*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

class UAuraUserWidget;
class UAbilityInfo;
class UAuraAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);  // Dynamic means it can blueprints assignable and adding multicast means it can bind to other blueprints if not dynamic only multicast then it can bind to other function (only in c++).
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelChangedSignature, int32, NewLevel, bool, bLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


/*
 Now, rather than just broadcasting a gameplay tag up to the widget side of things, I'd like to have

some kind of asset that we can use to look up information that we can broadcast to the widgets.

For example, we may have a asset such as a data table that can look things up by tag, by gameplay

tag and retrieve some kind of information, some kind of struct that we can pass up to the widgets.

So I'd like to make a data table that has information related to gameplay tags specifically for showing

messages to the screen.

And this data table is going to have its row structure defined here in C++ we can define the

row structure as a struct in C++,

*/
/*
The row has all the information to identify that specific bundle of data.

It has a gameplay tag.

It has the message.

*/

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	 
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;   // "OnHealthChanged" is actual delegate and "FOnAttributeChangedSignature" is delegate signature.

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnAttributeChangedSignature OnXPPercentChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Level")
	FOnLevelChangedSignature OnPlayerLevelChangedDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag); // template function to find data table and return the row ,no matter what the row type is.

	void OnXPChanged(int32 NewXP);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const;
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
