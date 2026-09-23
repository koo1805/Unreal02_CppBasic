// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = "Name";
	//Year = 98;

	// 시작할 때 카드가 생성되도록 객체 생성(CDO에서 관리됨)
	// CreateDefaultSubobject 함수는 생성자에서만 사용 가능함
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card"));
}

//void UPerson::DoLesson()
//{
//	UE_LOG(LogTemp, Log, TEXT("%s님이 수업에 참여합니다."), *Name);
//}
