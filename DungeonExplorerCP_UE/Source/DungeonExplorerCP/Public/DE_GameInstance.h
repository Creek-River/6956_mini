// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// datatime�\���̂��������߂ɕK�{
#include "Runtime/Core/Public/Misc/Timespan.h"
#include "DE_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class DUNGEONEXPLORERCP_API UDE_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// �v���C���[�c�@
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		int32 playerNum = 3;

	// ��ɂ������Ă�������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		int32 rockNum = 2;


	// �Q�[���J�n����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		FDateTime startTime;

};
