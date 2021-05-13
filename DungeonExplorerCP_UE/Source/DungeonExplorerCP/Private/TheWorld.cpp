// Fill out your copyright notice in the Description page of Project Settings.


#include "TheWorld.h"

#include "EnemyAIController.h"
#include "EnemyCPCharacter.h" // エネミーキャラクタを扱ううえで必要

// Sets default values
ATheWorld::ATheWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheWorld::BeginPlay()
{
	Super::BeginPlay();
	// オーバーラップイベントにデリゲート関数をバインドする
	WorldItemMeshComp->OnComponentBeginOverlap.AddDynamic(this, &ATheWorld::BeginOverlap);
}

// Called every frame
void ATheWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// オーバーラップイベントで実行するデリゲート
void ATheWorld::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// ここで敵キャラクターをフリーズさせる
	//enemyCharacter->//ポーズさせるメソッド
	// Waypoint取得のため、enemyCharacterを取得
	//AEnemyCPCharacter* enemyCharacter = Cast<AEnemyCPCharacter>(GetPawn());
	//enemyCharacter->AAIController->onWorld();

	this->Destroy();
	FString message = TEXT("The World 5sec");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
	//UE_LOG(LogTemp, Warning, TEXT("Got The World!!"));
}


