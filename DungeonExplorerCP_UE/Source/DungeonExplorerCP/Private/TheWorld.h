// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// ai�R���g���[���[
//#include "EnemyAIController.h"

// Static Mesh Component�����������ŕK�{
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h" 

#include "TheWorld.generated.h"

UCLASS()
class ATheWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheWorld();


	// �L�[�A�C�e��StaticMesh�Q�Ɨp�̃R���|�[�l���g
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		class UStaticMeshComponent* WorldItemMeshComp;


	// �A�C�e���擾��ɑ��삷��G�l�~�[�̎Q��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MomomoWorks")
		class AEnemyCPCharacter* enemyCharacter;
		// AEnemyCPCharacter* enemyCharacter;

	// �I�[�o�[���b�v�C�x���g�Ŏ��s����f���Q�[�g
	UFUNCTION()	// BP����͌Ă΂Ȃ����A���ꂪ�Ȃ��ƃf���Q�[�g���Ă΂�Ȃ�
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
