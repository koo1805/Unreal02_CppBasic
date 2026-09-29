// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObject.h"

void UMyObject::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	// 직렬화
	Ar << Order;
	Ar << Name;
}
