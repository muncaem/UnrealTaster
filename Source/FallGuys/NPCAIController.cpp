// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "NPCBase.h"

void ANPCAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (Result.IsSuccess())
	{
		if (ANPCBase* NPC = Cast<ANPCBase>(GetPawn()))
		{
			NPC->HandleMoveComplete(); // 다음 지점 이동
		}
	}

	// [ 필요 요소	AIController에서 할 수 있는 일 ]
	//	NPC가 이동 완료 후 자동 반응	- OnMoveCompleted()
	//	특정 위치 도달 후 행동 다르게 하기	- 위치 조건 체크 후 Command 전송
	//	플레이어 감지 후 대화 시작	- AIPerceptionComponent 활용
	//	Quest NPC는 말 걸고, 시민은 무반응	- 상태 플래그 분기 or Controller 종류 나누기
}
