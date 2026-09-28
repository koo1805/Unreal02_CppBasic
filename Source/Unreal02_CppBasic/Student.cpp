// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("학생");
	//Year = 1;
	//Id = 1;

	// 카드 타입 설정
	Card->SetCardType(ECardType::Student);
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	// 로그 출력
	UE_LOG(LogTemp, Log, TEXT("[Student] %s님이 %s로부터 받은 메세지: %s"), *Name, *School, *NewCourseInfo);
}

void UStudent::DoLesson()
{
	ILessonInterface::DoLesson();

	UE_LOG(LogTemp, Log, TEXT("%s님이 수업을 듣습니다."), *Name);
}
