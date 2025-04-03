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
	if (!SunLight || !SkyLight) return;

	// 해 각도 계산
	float SunPitch = ((TimeOfDay - 6) / 12.f) * 180.f - 90.f;
	FRotator NewRotation = FRotator(SunPitch, -90.f, 0.f);
	SunLight->SetActorRotation(NewRotation);


	// Directional Light (태양)
	float MinSunIntensity = 0.3f;  // 기존 0.01 → 이제 0.3 이상
	float MaxSunIntensity = 6.0f;

	float SunFactor = FMath::Clamp(FMath::Cos(FMath::DegreesToRadians(SunPitch)), 0.f, 1.f);
	float FinalSunIntensity = FMath::Lerp(MinSunIntensity, MaxSunIntensity, SunFactor);
	SunLight->GetLightComponent()->SetIntensity(FinalSunIntensity);

	// SkyLight 조절
	float MinSkyIntensity = 0.1f;
	float MaxSkyIntensity = 2.0f;

	float SkyFactor = SunFactor;  // 같은 기준 사용
	float FinalSkyIntensity = FMath::Lerp(MinSkyIntensity, MaxSkyIntensity, SkyFactor);
	SkyLight->GetLightComponent()->SetIntensity(FinalSkyIntensity);
	SkyLight->GetLightComponent()->RecaptureSky();


	// 하늘 머터리얼도 업데이트
	if (SkySphereActor)
	{
		UFunction* UpdateFunc = SkySphereActor->FindFunction(FName("UpdateSunDirection"));
		if (UpdateFunc)
			SkySphereActor->ProcessEvent(UpdateFunc, nullptr);
	}

	// Night용 조명
	bool bIsNight = (TimeOfDay < 6 || TimeOfDay > 18);
	if (MoonLight)
	{
		MoonLight->SetActorHiddenInGame(!bIsNight);
		MoonLight->GetLightComponent()->SetIntensity(bIsNight ? 0.5f : 0.f); // 아주 부드럽게
	}

}
