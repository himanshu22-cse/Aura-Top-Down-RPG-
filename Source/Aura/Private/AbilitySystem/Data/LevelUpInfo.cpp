
#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;

	/*
it's a while loop.

So the maximum number of iterations would be the length of our array.

And this also allows us to see what level we should be for any XP amount.
	*/

	while (bSearching)
	{
		// LevelUpInformation[1] = Level 1 Information
		// LevelUpInformation[2] = Level 1 Information
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)  // As "LevelUpInformation" at "Level" return struct so we use dot operator to so we can access that level up requirement and that will tell how much we have to level up at this particular level
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
