// Fill out your copyright notice in the Description page of Project Settings.


#include "DE_PlayerController.h"

void ADE_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	{
		if (W_MainHUD) {
			// widget���쐬
			DE_MainHUD = CreateWidget<UMainHUD>(this, W_MainHUD);

			if (DE_MainHUD) {
				// ��������HUD���r���[�|�[�g�ɕ\��
				DE_MainHUD->AddToViewport();
			}
			// �{�^����������悤�Ƀ}�E�X����̋���
			bShowMouseCursor = true;
		}


	}



}