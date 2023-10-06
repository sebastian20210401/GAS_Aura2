// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"


void UAuraGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (!bInit)
	{
		TimePressed = GetWorld()->TimeSeconds;
		bInit = true;
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString::Printf(TEXT("InputPressed: %f"), TimePressed));
	}
}

void UAuraGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	TimeReleased = GetWorld()->TimeSeconds;
	bInit = false;

	GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Green, FString::Printf(TEXT("InputReleased: %f"), TimeReleased));
	GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Cyan, FString::Printf(TEXT("Elapsed Time: %f"), TimeReleased - TimePressed));

	//UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	//if (AbilitySystemComponent != nullptr && IsValidChecked(AbilitySystemComponent))
	//{
	//	FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
	//	FGameplayEventData Payload;
	//	AbilitySystemComponent->HandleGameplayEvent(EventTag, &Payload);
	//}
}

void UAuraGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (bInit)
	{
		TimeReleased = GetWorld()->TimeSeconds;
		bInit = false;
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Green, FString::Printf(TEXT("InputReleased: %f"), TimeReleased));
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Cyan, FString::Printf(TEXT("Elapsed Time: %f"), TimeReleased - TimePressed));
	}

}
