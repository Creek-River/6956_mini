// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

// �Q�[���C���X�^���X�擾�Ɏg��
#include "Runtime/Engine/Classes/Kismet/GamePlayStatics.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"

void UMainHUD::NativeConstruct()
{

	Super::NativeConstruct();

	// �������Ԓl��TimeSpan�^�ɕϊ����Ă���
	limitTime = FTimespan(0, (int)limitSeconds / 60, (int)limitSeconds % 60);

	// �Q�[���C���X�^���X�擾
	DE_instance = Cast<UDE_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (DE_instance != NULL) {
		if (DE_instance->playerNum == 3) {
			DE_instance->startTime = FDateTime::Now();
		}
	}
}

void UMainHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// �c�莞�Ԃ̎Z�o
	remainTime = limitTime - (FDateTime::Now() - DE_instance->startTime);

	if (this->GetRemainSeconds() == 0) {
		// �Swidget������
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		if (WidgetBP_GameOver) {
			WidgetBP_GameOver->AddToViewport();
		}
	}
}

int32 UMainHUD::GetRemainSeconds()
{
	return (int)(remainTime.GetMinutes() * 60 + remainTime.GetSeconds());
}

