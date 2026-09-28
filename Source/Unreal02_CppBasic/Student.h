// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Person.h"
#include "LessonInterface.h"
#include "Student.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL02_CPPBASIC_API UStudent : public UPerson, public ILessonInterface
{
	GENERATED_BODY()

public:
	UStudent();

	// 알림 메시지를 수신할 함수 선언.
	void GetNotification(const FString& School, const FString& NewCourseInfo);

private:
	virtual void DoLesson() override;
	//UPROPERTY()
	//int32 Id;
};
