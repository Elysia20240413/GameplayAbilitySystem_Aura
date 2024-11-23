// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interface/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	if(GetAvatarActorFromActorInfo()->HasAuthority())
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
		if(CombatInterface)
		{
			const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
			FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
			Rotation.Pitch = 0.f;
			
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SocketLocation);
			SpawnTransform.SetRotation(Rotation.Quaternion());
			
			AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
				ProjectileClass,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			const UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo_Checked();
			Projectile->DamageEffectSpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
			Projectile->TagEffectSpecHandle = SourceASC->MakeOutgoingSpec(TagEffectClass, GetAbilityLevel(),SourceASC->MakeEffectContext());

			const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
			const float ScaledDamage = Damage.GetValueAtLevel(10);
			
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Projectile->DamageEffectSpecHandle, GameplayTags.Damage, ScaledDamage);
			
			Projectile->FinishSpawning(SpawnTransform);
		}
	}
}
