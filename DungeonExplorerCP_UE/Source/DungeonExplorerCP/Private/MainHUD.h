// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "DE_GameInstance.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "Runtime/Core/Public/Misc/Timespan.h"

#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class UMainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		float limitSeconds = 60.0f;

	UFUNCTION(BlueprintCallable, Category = "MomomoWorks")
		int32 GetRemainSeconds();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		UUserWidget* WidgetBP_GameOver;

	UDE_GameInstance* DE_instance;
	FTimespan limitTime, remainTime;

	// widget�\�z���ɃR�[�������
	virtual void NativeConstruct() override;

	// widget�ł�tick�C�x���g
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
};
