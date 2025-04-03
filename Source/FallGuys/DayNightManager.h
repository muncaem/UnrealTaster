// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DayNightManager.generated.h"

class ADirectionalLight;
class ASkyLight;
class AActor;

/**
 * 
 */
UCLASS()
class FALLGUYS_API ADayNightManager : public AActor
{
	GENERATED_BODY()

public:
	ADayNightManager();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Time")
	float SecondsPerDay = 600; //하루에 부여된 초. => 600초(10분).

	UPROPERTY(VisibleAnywhere, Category = "Time")
	float TimeOfDay = 6; // 24시간제 | 스타트 시, 현재 시간.

	UPROPERTY(EditAnywhere, Category = "Lighting")
	TObjectPtr<ADirectionalLight> SunLight; //태양 조명

	UPROPERTY(EditAnywhere, Category = "Lighting")
	TObjectPtr<AActor> SkySphereActor; // SkySphere Actor

	UPROPERTY(EditAnywhere, Category = "Lighting")
	TObjectPtr<ASkyLight> SkyLight; // SkyLight 전체 조명 캡처

	UPROPERTY(EditAnywhere)
	TObjectPtr<ADirectionalLight> MoonLight; // 밤 전용 조명

private:
	void UpdateSun();
};
