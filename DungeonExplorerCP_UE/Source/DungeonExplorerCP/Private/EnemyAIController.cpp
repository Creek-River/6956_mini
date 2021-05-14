 // Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCPCharacter.h" // �G�l�~�[�L�����N�^�����������ŕK�v

// tuiki
#include "TheWorld.h"
#include "Keyitem.h"
#include "EnemyCPCharacter.h"
#include "EngineUtils.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h" // �v���C���[�L�����N�^���擾�̂��߂ɕK�v
#include "DE_GameInstance.h"// �Q�[���C���X�^���X�Ɋi�[���Ă���c�@���擾�̂��ߒǉ�

// �R���X�g���N�^
AEnemyAIController::AEnemyAIController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// BlackBoard�R���|�[�l���g���쐬
	bb = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board"));
	bb->SetValueAsBool("OnWorld", false);
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

	/*
	for (TObjectIterator<ATheWorld> Itr; Itr; ++Itr)
	{
		ATheWorld* mesh = *Itr;
		FString actorName = Itr->GetName();
		if (!actorName.MatchesWildcard("*TheWorld*")) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "a" + mesh->GetName());
			OnWorld();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "a" + mesh->GetName());
			//break;
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "aaa");
	}
	*/
	

	/*
	for (TObjectIterator<AKeyItem> Itr; Itr; ++Itr)
	{
		AKeyItem* mesh = *Itr;
		FString actorName = Itr->GetName();
		if (actorName.MatchesWildcard("*KeyItem*")) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, mesh->GetName());
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "ooo");
			break;
		}

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "iii");
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, mesh->GetName());
	}
	*/

}


// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FString playerName = UGameplayStatics::GetPlayerCharacter(this, 0)->GetName(); // �v���C���[�̃C���X�^���X�����擾
	/*
	TSubclassOf<ATheWorld> theWorld;
	TSubclassOf<AKeyItem> keys;
	TArray<AActor*> my1Array;
	TArray<AActor*> my2Array;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), theWorld, my1Array);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), keys, my2Array);
	

	// GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Format(TEXT("{0}", my1Array.Num() ) ) );
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%d"), my1Array.Num() ) );
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%d"), my2Array.Num()));
	// 0���傫����

	if (my1Array.Num() == 0) {

		OnWorld();
	}
	if (my2Array.Num() == 0) {

		//�G���i���ɒǂ��Ă��鏈��������
	}
	*/
	/*
	TSubclassOf<AActor> actors;
	TArray<AActor*> Array;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), actors, Array);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("%d"), Array.Num()));
	*/
	
	UDE_GameInstance* DE_instance = Cast<UDE_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	for (TObjectIterator<ATheWorld> Itr; Itr; ++Itr)
	{
		ATheWorld* mesh = *Itr;
		FString actorName = Itr->GetName();
		if (DE_instance->test) {
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "a" + mesh->GetName());
			OnWorld();
			DE_instance->test = false;
			break;
		}
		else {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "a" + mesh->GetName());
			//break;
		}
	}
	

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
void AEnemyAIController::OnWorld()
{
	// �l��true�ɍX�V
	bb->SetValueAsBool("OnWorld", true);

}

