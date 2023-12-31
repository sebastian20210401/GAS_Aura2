// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag/*FAuraGameplayTags::Get().CombatSocket_Weapon*/);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	//const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	//FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();


	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	//FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	//EffectContextHandle.SetAbility(this);
	//EffectContextHandle.AddSourceObject(Projectile);
	//TArray<TWeakObjectPtr<AActor>> Actors;
	//Actors.Add(Projectile);
	//EffectContextHandle.AddActors(Actors);
	//FHitResult HitResult;
	//HitResult.Location = ProjectileTargetLocation;
	//EffectContextHandle.AddHitResult(HitResult);
	//	
	//const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

	//const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();


	//const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	//UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageType, ScaledDamage);



	//if (CooldownTag.IsValid())
	//{
	//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, CooldownTag, AbilityCooldown);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), AbilityCooldown));
	//}
	
	// Important!!!
	//Projectile->DamageEffectSpecHandle = SpecHandle;
	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();

	Projectile->FinishSpawning(SpawnTransform);
	
}
