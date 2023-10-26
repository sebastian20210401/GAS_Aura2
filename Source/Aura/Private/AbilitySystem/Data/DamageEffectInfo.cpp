// Copyright Druid Mechanics


#include "AbilitySystem/Data/DamageEffectInfo.h"
#include "Aura/AuraLogChannels.h"

FAuraDamageEffectInfo UDamageEffectInfo::FindDamageEffectInfoForTag(const FGameplayTag& DamageEffectTag, bool bLogNotFound) const
{
	for (const FAuraDamageEffectInfo& Info : DamageEffectInformation)
	{
		if (Info.DamageEffectTag == DamageEffectTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogAura, Error, TEXT("Can't find info for DamageEffectTag [%s] on DamageEffectInfo [%s]"), *DamageEffectTag.ToString(), *GetNameSafe(this));
	}

	return FAuraDamageEffectInfo();
}
