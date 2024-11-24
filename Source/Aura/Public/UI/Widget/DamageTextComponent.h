// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:

	//TODO:使用对象池优化文本的创建，以免爆栈，可以借鉴Lyra
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage);
};
