// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "character/AuraCharacter.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgtController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacter,public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** end Enemy Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Default")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
