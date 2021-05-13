 // Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCPCharacter.h" // �G�l�~�[�L�����N�^�����������ŕK�v

// �R���X�g���N�^
AEnemyAIController::AEnemyAIController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// BlackBoard�R���|�[�l���g���쐬
	bb = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	// Waypoint�擾�̂��߁AenemyCharacter���擾
	AEnemyCPCharacter* enemyCharacter = Cast<AEnemyCPCharacter>(GetPawn());

	if (bt != NULL)
		RunBehaviorTree(bt); // BT���N��
	if (bb != NULL) {
		// Waypoint���擾���ABB�L�[�l�Ƃ��ēo�^
		for (int i = 0; i < enemyCharacter->waypointTargets.Num(); i++) {
			FString key = "waypoint" + FString::FromInt(i + 1);
			bb->SetValueAsObject(*key, enemyCharacter->waypointTargets[i]);
		}
	}

	// Pawn Sensor�̃p�����[�^�ݒ�
	PawnSensor->SightRadius = 900.0f;
	PawnSensor->SensingInterval = 0.5f;
	PawnSensor->bEnableSensingUpdates = true;
	PawnSensor->bOnlySensePlayers = false;
	PawnSensor->SetPeripheralVisionAngle(30.0f);
	// Delegate��o�^
	FScriptDelegate OnSeePawnDelegate;
	OnSeePawnDelegate.BindUFunction(this, "OnSeePawn");
	PawnSensor->OnSeePawn.Add(OnSeePawnDelegate);
	FScriptDelegate OnHearNoiseDelegate;
	OnHearNoiseDelegate.BindUFunction(this, "OnHearNoise");
	PawnSensor->OnHearNoise.Add(OnHearNoiseDelegate);
}

void AEnemyAIController::OnHearNoise(APawn *OtherActor, const FVector &Location, float Volume)
{

	// ����͎����Ȃ�    
}

void AEnemyAIController::OnSeePawn(APawn *OtherPawn)
{
	// �f�o�b�O�o��
	FString message = TEXT("Saw Pawn ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	bb->SetValueAsObject("Player", OtherPawn); // Player�L�[�l�����
	// �R�[���o�b�N�̃^�C�}�[����
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemyAIController::OnChaseTimeOut, 3.0f, true);
}

// �^�C�}�[����R�[�������
void AEnemyAIController::OnChaseTimeOut()
{
	// �L�[�l��NULL�ɐݒ肵�ď���s���ɖ߂�
	bb->SetValueAsObject("Player", NULL);
	// �f�o�b�O�o��
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Timeout");
}

// eyechar��world�ɏՓ˂�����A������Ăяo��
void AEnemyAIController::OnWorld(APawn* OtherPawn)
{
	bb->SetValueAsObject("OnWorld", OtherPawn); // Player�L�[�l�����

}

