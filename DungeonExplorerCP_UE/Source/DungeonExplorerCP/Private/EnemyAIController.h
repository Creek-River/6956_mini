// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

// Behavior Tree�֘A�̃w�b�_�ǉ�
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

// Pawn Sensing�ɕK�v
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"

#include "EnemyAIController.generated.h"

UCLASS()
class AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	// �R���X�g���N�^�@�R���|�[�l���g�������̂���FObjectInitializer�ł��K�v
	AEnemyAIController(const class FObjectInitializer& PCIP);

protected:
	UPROPERTY(BlueprintReadWrite)
		class UBehaviorTree* bt; // Bevior Tree

	UPROPERTY(BlueprintReadWrite)
		class UBlackboardComponent* bb; // Blackboard
	
	virtual void BeginPlay() override; // Begin Play��錾

	// Pawn Sensing
	UPROPERTY(BlueprintReadWrite)
		class UPawnSensingComponent* PawnSensor;

	// Pawn Sensing���m�C�Y�𒮂����Ƃ��ɌĂԃR�[���o�b�N
	UFUNCTION()
		void OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume);

	// Pawn Sensing��Pawn�����F�����Ƃ��ɌĂԃR�[���o�b�N
	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);


	// TheWorld�ɂ��������Ƃ�
	UFUNCTION()
		void OnWorld();

	// �^�C�}�[�p
	FTimerHandle timerHandle;
	void OnChaseTimeOut();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
