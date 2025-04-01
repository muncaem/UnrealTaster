// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightManager.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"

ADayNightManager::ADayNightManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADayNightManager::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green,
		FString::Printf(TEXT("BeginPlay TimeOfDay: %.2f"), TimeOfDay));

	UpdateSun();
}

void ADayNightManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 하루 시간 흐름
	TimeOfDay += (DeltaTime * 24) / SecondsPerDay;
	if (TimeOfDay >= 24)
		TimeOfDay -= 24;

	UpdateSun();

	FTimerHandle ForceSunHandle;
	GetWorldTimerManager().SetTimer(ForceSunHandle, this, &ADayNightManager::UpdateSun, 0.1f, false);
}

void ADayNightManager::UpdateSun()
{
	if (!SunLight) return;

	// 6시는 0도 => 동쪽 지평선에서 시작.
	float SunPitch = ((TimeOfDay - 6) / 12.f) * 180.f - 90.f;
	
	// Sun 회전각 조절
	FRotator NewRotation = FRotator(SunPitch, -90.f, 0.f);
	SunLight->SetActorRotation(NewRotation);

	// 아침/저녁 보정용: 코사인 커브 기반 조절
	float SunAngleRad = FMath::DegreesToRadians(SunPitch);
	float RawFactor = FMath::Clamp(FMath::Cos(SunAngleRad), 0.f, 1.f); // 0~1 사이
	float AdjustedFactor = FMath::Lerp(0.2f, 1.0f, RawFactor); // 기본 밝기 0.2부터 시작
	//최종밝기
	float FinalIntensity = 5000.f * AdjustedFactor;
	SunLight->GetLightComponent()->SetIntensity(FinalIntensity);

	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	5.0f,
	//	FColor::Red,
	//	FString::Printf(TEXT("TimeOfDay: %.2f, Intensity: %.2f , NewRotation: %s"),
	//		TimeOfDay,
	//		Intensity,
	//		*NewRotation.ToString()) // Rotator는 .ToString() 후 * 로 FString → TCHAR* 변환
	//);


	// 하늘 텍스처 업데이트 -> 해처럼 보이는 부분 렌더링
	if (SkySphereActor)
	{
		UFunction* UpdateFunc = SkySphereActor->FindFunction(FName("UpdateSunDirection"));
		if (UpdateFunc)
			SkySphereActor->ProcessEvent(UpdateFunc, nullptr);

		/*UFunction* RefreshFunc = SkySphereActor->FindFunction(FName("RefreshMaterial"));
		if (RefreshFunc)
		{
			SkySphereActor->ProcessEvent(RefreshFunc, nullptr);
		}*/
	}

	if (SkyLight && SkyLight->GetLightComponent())
	{
		SkyLight->GetLightComponent()->RecaptureSky();
	}
}
