// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCBase.h"
#include "NPCAIController.h"

// Sets default values
ANPCBase::ANPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	//GetController() → 현재 Pawn에 붙은 컨트롤러 (플레이어든 AI든)
	DefaultAIController = Cast<AAIController>(GetController()); //=> 직접할당 안해줘도 BP에서 할당하면 자동 할당됨.
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::Printf(TEXT("PatrolPointA: %s, PatrolPointB"), 
	//	*PatrolPointA->GetName(), *PatrolPointB->GetName()));

	if (bCanPatrol && nullptr != PatrolPointA && nullptr != PatrolPointB)
	{
		CurrentTargetPoint = PatrolPointA;
		MoveToTarget();
	}
}

// Called every frame
void ANPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ANPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCBase::HandleMoveComplete()
{
	if (bIsTalking || !bCanPatrol) return;

	SwitchTarget();
	MoveToTarget();
}

void ANPCBase::OnPlayerInteract()
{
	if (!bCanInteract || bIsTalking) return;

	bIsTalking = true;

	// 대화 시작 → UI 호출 or 애니메이션
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("NPC Communacation Start")));

	// 이동 멈추기
	if (DefaultAIController)
		DefaultAIController->StopMovement();
}

void ANPCBase::MoveToTarget()
{
	if (DefaultAIController && CurrentTargetPoint)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(CurrentTargetPoint);
		MoveRequest.SetAcceptanceRadius(100);

		FNavPathSharedPtr NavPath;
		DefaultAIController->MoveTo(MoveRequest, &NavPath);
		// => 완료 후, NPCAIController의 OnMoveCompleted()에서 감지 후 HandleMoveComplete()호출
	}
}

void ANPCBase::SwitchTarget()
{
	if (!PatrolPointA && !PatrolPointB) return;

	CurrentTargetPoint = (CurrentTargetPoint == PatrolPointA) ? PatrolPointB : PatrolPointA;
}
