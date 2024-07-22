#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"


UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
    GENERATED_BODY()

public:

    /*
   So that's the first thing we have to do is we need to define the get function which will return this

    actual type.

   Now, once we've done that, our asset manager needs to override a function that exists on the asset

   manager class.

  That's a protected function.

    So we'll make a protected section and it's a virtual void function called Start initial loading.

  This is called very early on and this is when we start the initial loading for our assets for the game.

    And this is the perfect place for us to call that initialize native tags function that we have here

    in our gameplay tags.

   It's a static function.
   */
    static UAuraAssetManager& Get();

protected:

    virtual void StartInitialLoading() override;
};
