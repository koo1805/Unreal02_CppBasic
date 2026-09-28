// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CourseInfo.generated.h"

// 델리게이트 선언.
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCourseInfoChangedSignature, const FString&, const FString&);

/**
 * 
 */
UCLASS()
class UNREAL02_CPPBASIC_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	FOnCourseInfoChangedSignature OnChanged;

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	FString Contents;
};
