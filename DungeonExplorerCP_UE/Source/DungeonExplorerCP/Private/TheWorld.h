// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// aiコントローラー
//#include "EnemyAIController.h"

// Static Mesh Componentを扱ううえで必須
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h" 

#include "TheWorld.generated.h"

UCLASS()
class ATheWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheWorld();


	// キーアイテムStaticMesh参照用のコンポーネント
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		class UStaticMeshComponent* WorldItemMeshComp;


	// アイテム取得後に操作するエネミーの参照
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		class AEnemyCPCharacter* enemyCharacter;
		// AEnemyCPCharacter* enemyCharacter;

	// オーバーラップイベントで実行するデリゲート
	UFUNCTION()	// BPからは呼ばないが、これがないとデリゲートが呼ばれない
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
