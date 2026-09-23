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


private:
	virtual void DoLesson() override;
	//UPROPERTY()
	//int32 Id;
};
