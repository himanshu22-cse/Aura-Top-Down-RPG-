#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

class UGameplayAbility;
UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

// saving data related to Actors
USTRUCT()
struct FSavedActor
{
	GENERATED_BODY()


		UPROPERTY()
		FName ActorName = FName(); // if the actors that you're saving and loading are persistent, such as our checkpoints, their names should remain constant.

	UPROPERTY()
		FTransform Transform = FTransform();  //ome of your actors that you're saving and loading may have a transform or in other words, a location rotationand scale  And if you'd like to save that transform,  .

		/*
		Now you could add any number of other variables here, such as gameplay tags like our saved ability

		has, but there's also a way to serialize an actor and save any number of its member variables, provided

		that those member variables are marked with a specific U property specifier.

		 That specifier is savegame, and we'll see how that works, and the way that you can serialize that

		 data on the actor for all variables marked with this specifier is to have a t array of bytes.

		Now we can represent a byte which is eight bits of data as a u int eight.

		Because a u int eight is an unsigned eight bit integer and a t array of u, int eight is an array of bytes.

		We can call this bytes, and we can give it a u property.

		And I'm going to give this a comment that says contains serialized, not really contains, but it is

		serialized variables from the actor.

		Only those marked with save game specifier.

		So that's what bytes is going to contain.
		*/
	UPROPERTY()
		TArray<uint8> Bytes;// Serialized variables from the Actor - only those marked with SaveGame specifier

};

inline bool operator==(const FSavedActor& Left, const FSavedActor& Right)
{
	return Left.ActorName == Right.ActorName;
}

USTRUCT()
struct FSavedMap
{
	GENERATED_BODY()

		UPROPERTY()
		FString MapAssetName = FString();

	//An fsaved map can be identified by its map asset name, and then it can contain an array of all of its saved actor data.
	UPROPERTY()
		TArray<FSavedActor> SavedActors;

};

// Struct For Store the information of Ability.
USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ClassDefaults")
		TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FGameplayTag AbilityStatus = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FGameplayTag AbilitySlot = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FGameplayTag AbilityType = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 AbilityLevel = 1;
};

inline bool operator==(const FSavedAbility& Left, const FSavedAbility& Right)
{
	return Left.AbilityTag.MatchesTagExact(Right.AbilityTag);
}


UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY()
		FString SlotName = FString();

	UPROPERTY()
		int32 SlotIndex = 0;

	/*
what if you want to save one slot with your name, and then save another slot with the same name?

You couldn't do that if you were using the name to identify your save slot.

So we're going to have player name as a separate variable.
*/

	UPROPERTY()
		FString PlayerName = FString("Default Name");

	UPROPERTY()
		FString MapName = FString("Default Map Name");

	UPROPERTY()
		FString MapAssetName = FString("Default Map Asset Name");

	UPROPERTY()
		FName PlayerStartTag;

	UPROPERTY()
		TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	UPROPERTY()
		bool bFirstTimeLoadIn = true;

	/* Player */

	UPROPERTY()
		int32 PlayerLevel = 1;

	UPROPERTY()
		int32 XP = 0;

	UPROPERTY()
		int32 SpellPoints = 0;

	UPROPERTY()
		int32 AttributePoints = 0;

	UPROPERTY()
		float Strength = 0;

	UPROPERTY()
		float Intelligence = 0;

	UPROPERTY()
		float Resilience = 0;

	UPROPERTY()
		float Vigor = 0;

	/* Abilities */

	UPROPERTY()
		TArray<FSavedAbility> SavedAbilities; // As we want to save all of our abilities so we can have a array if FSavedAbility.

	UPROPERTY()
		TArray<FSavedMap> SavedMaps; //And because we can have any number of maps that we've been to that we may wish to save actors for.

	FSavedMap GetSavedMapWithMapName(const FString& InMapName);
	bool HasMap(const FString& InMapName);
};
