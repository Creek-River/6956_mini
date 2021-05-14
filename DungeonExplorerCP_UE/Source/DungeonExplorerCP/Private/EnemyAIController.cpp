 // Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCPCharacter.h" // エネミーキャラクタを扱ううえで必要

// tuiki
#include "TheWorld.h"
#include "Keyitem.h"
#include "EnemyCPCharacter.h"
#include "EngineUtils.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h" // プレイヤーキャラクタ情報取得のために必要
#include "DE_GameInstance.h"// ゲームインスタンスに格納している残機情報取得のため追加

// コンストラクタ
AEnemyAIController::AEnemyAIController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	// BlackBoardコンポーネントを作成
	bb = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Black Board"));
	bb->SetValueAsBool("OnWorld", false);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	// Waypoint取得のため、enemyCharacterを取得
	AEnemyCPCharacter* enemyCharacter = Cast<AEnemyCPCharacter>(GetPawn());

	if (bt != NULL)
		RunBehaviorTree(bt); // BTを起動
	if (bb != NULL) {
		// Waypointを取得し、BBキー値として登録
		for (int i = 0; i < enemyCharacter->waypointTargets.Num(); i++) {
			FString key = "waypoint" + FString::FromInt(i + 1);
			bb->SetValueAsObject(*key, enemyCharacter->waypointTargets[i]);
		}
	}

	// Pawn Sensorのパラメータ設定
	PawnSensor->SightRadius = 900.0f;
	PawnSensor->SensingInterval = 0.5f;
	PawnSensor->bEnableSensingUpdates = true;
	PawnSensor->bOnlySensePlayers = false;
	PawnSensor->SetPeripheralVisionAngle(30.0f);


	// Delegateを登録
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
	//FString playerName = UGameplayStatics::GetPlayerCharacter(this, 0)->GetName(); // プレイヤーのインスタンス名を取得
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
	// 0より大きいか

	if (my1Array.Num() == 0) {

		OnWorld();
	}
	if (my2Array.Num() == 0) {

		//敵が永遠に追ってくる処理をつくる
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

	// 今回は実装なし    
}

void AEnemyAIController::OnSeePawn(APawn *OtherPawn)
{
	// デバッグ出力
	FString message = TEXT("Saw Pawn ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	bb->SetValueAsObject("Player", OtherPawn); // Playerキー値を入力
	// コールバックのタイマー発動
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemyAIController::OnChaseTimeOut, 3.0f, true);
}

// タイマーからコールされる
void AEnemyAIController::OnChaseTimeOut()
{
	// キー値をNULLに設定して巡回行動に戻す
	bb->SetValueAsObject("Player", NULL);
	// デバッグ出力
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Timeout");
}

// eyecharがworldに衝突したら、これを呼び出す
void AEnemyAIController::OnWorld()
{
	// 値をtrueに更新
	bb->SetValueAsBool("OnWorld", true);

}

