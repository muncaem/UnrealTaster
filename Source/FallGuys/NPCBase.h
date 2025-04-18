// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "NPCBase.generated.h"

UCLASS()
class FALLGUYS_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<AAIController> DefaultAIController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bCanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	bool bCanPatrol = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	TObjectPtr<AActor> PatrolPointA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	TObjectPtr<AActor> PatrolPointB;

	TObjectPtr<AActor> CurrentTargetPoint;

	//// 선택적으로 바인딩할 델리게이트
	//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNPCInteracted);

	//UPROPERTY(BlueprintAssignable)
	//FOnNPCInteracted OnInteracted;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsTalking = false;

public:
	UFUNCTION()
	void HandleMoveComplete();  // AIController가 호출

	UFUNCTION()
	void OnPlayerInteract();    // 플레이어가 직접 호출

protected:
	void MoveToTarget();
	void SwitchTarget();

	//FTimerHandle PatrolTimerHandle;



	//void Interact()
	//{
	//	if (bCanInteract)
	//	{
	//		OnInteracted.Broadcast();
	//	}
	//}
	// 
	//그리고 상호작용이 필요한 NPC에서만:
	/*class AMerchantNPC : public ANPCBase
	{
		virtual void BeginPlay() override
		{
			bCanInteract = true;

			OnInteracted.AddDynamic(this, &AMerchantNPC::OpenShopUI);
		}

		UFUNCTION()
		void OpenShopUI();
	};*/

};
