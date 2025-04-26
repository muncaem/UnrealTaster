// Fill out your copyright notice in the Description page of Project Settings.


#include "EventHub.h"

UEventHub* UEventHub::Get()
{
    // 일시적인 인스턴스 생성(GC 관리) => 싱글톤처럼 동작. 결론 객체생성 코드
    static UEventHub* Hub = NewObject<UEventHub>();
    if (!Hub->IsRooted())
        Hub->AddToRoot();  // Root는 절대 지워지지 않음
    return Hub;
}

