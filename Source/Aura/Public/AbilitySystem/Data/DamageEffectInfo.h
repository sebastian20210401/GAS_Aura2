// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DamageEffectInfo.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAuraDamageEffectInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag DamageEffectTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffect;
};

UCLASS()
class AURA_API UDamageEffectInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray <FAuraDamageEffectInfo> DamageEffectInformation;

	FAuraDamageEffectInfo FindDamageEffectInfoForTag(const FGameplayTag& DamageEffectTag, bool bLogNotFound = false) const;

};
