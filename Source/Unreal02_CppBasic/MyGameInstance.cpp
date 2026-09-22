// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	// Output Log
	// Unreal use UTF16 -> WCHAR
	UE_LOG(LogTemp, Log, TEXT("Hello Unreal"));
}
