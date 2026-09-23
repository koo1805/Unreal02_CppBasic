// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Person.generated.h"

// 전방 선언
class UCard;

/**
 * 
 */
UCLASS()
class UNREAL02_CPPBASIC_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	// 관리받는 함수로 선언
	//UFUNCTION()
	//virtual void DoLesson();

	// Getter/Setter
	FORCEINLINE const FString& GetName() { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }

	FORCEINLINE UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(UCard* InCard) { Card = InCard; }

protected:
	// 관리 받는 속성으로 선언
	UPROPERTY()
	FString Name;

	UPROPERTY()
	TObjectPtr<UCard> Card;

	//UPROPERTY()
	//int32 Year;
};
