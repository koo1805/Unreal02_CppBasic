// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL02_CPPBASIC_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// 생성자
	UMyGameInstance();


private:
	virtual void Init() override;

private:
	UPROPERTY()
	FString SchoolName;
	
};
