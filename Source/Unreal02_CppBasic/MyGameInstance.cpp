// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"

UMyGameInstance::UMyGameInstance()
{
	// 기본값 설정
	// 생성자에서 설정하는 기본 값은 CDO 템플릿 객체에 저장
	SchoolName = TEXT("기본 학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	// 클래스 정보 가져오기 ======================================================================================
	UClass* ClassRuntime = GetClass();
	UClass* ClassCompile = UMyGameInstance::StaticClass();

	// 두 정보가 같은지를 비교 = assert
	//check(ClassRuntime != ClassCompile);
	//ensure(ClassRuntime != ClassCompile);

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	UE_LOG(LogTemp, Log, TEXT("학교 이름을 담당하는 클래스 이름: %s"), *ClassRuntime->GetName());

	SchoolName = TEXT("Soul");

	UE_LOG(LogTemp, Log, TEXT("학교 이름: %s"), *SchoolName);

	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값: %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);

	UE_LOG(LogTemp, Log, TEXT("============================================"));


	// Output Log ==============================================================================================
	// Unreal use UTF16 -> WCHAR
	// 각종 타입으로 변경할 수 있는 헬퍼 함수 제공
	//UE_LOG(LogTemp, Log, TEXT("Hello Unreal"));

	// TCHAR | FString
	TCHAR LogCharArray[] = TEXT("Hello Unreal");
	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArray);

	FString LogCharString = LogCharArray;
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);

	// 문자열 복사
	TCHAR LogCharArrayWithSize[100] = {};
	FCString::Strncpy(LogCharArrayWithSize, *LogCharString, LogCharString.Len());

	UE_LOG(LogTemp, Log, TEXT("%s"), LogCharArrayWithSize);

	// 문자열 자르기
	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))
	{
		// 문자열을 검색해 시작 인덱스 얻기
		int32 Index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase);
		FString EndString = LogCharString.Mid(Index);
		UE_LOG(LogTemp, Log, TEXT("%s"), *EndString);
	}

	// 문자열 나누기
	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right))
	{
		UE_LOG(LogTemp, Log, TEXT("Split Test: %s / %s"), *Left, *Right);
	}

	// 문자열 조합
	int32 IntValue = 40;
	float FloatValue = 3.141592f;

	FString FloatIntString = FString::Printf(TEXT("Int: %d, Float: %f"), IntValue, FloatValue);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);

	// FName 특성 - 대소문자 구별하지 않음
	FName Key01(TEXT("PELVIS"));
	FName Key02(TEXT("pelvis"));

	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과: %s"), (Key01 == Key02 ? TEXT("같음") : TEXT("다름")));

	// ====================================================================================================

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	// 학생 / 선생님 객체 생성
	TArray<UPerson*> Persons =
	{
		NewObject<UStudent>(),
		NewObject<UTeacher>(),
		NewObject<UStaff>()
	};

	// 범위 기반 루프 할용 이름 출력
	for (const auto Person : Persons)
	{
		UE_LOG(LogTemp, Log, TEXT("구성원 이름: %s"), *Person->GetName());
	}

	// 인터페이스 구현 여부에 따른 수업 참여 구분
	// 구현 여부 확인 방법 -> 해당 인터페이스로 형변환(다운 캐스팅)
	// 다운 캐스팅 RTTI
	for (const auto Person : Persons)
	{
		// 형변환을 통한 인터페이스 구현 여부 확인
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);

		// 형변환에 성공했다면 -> 구현한 경우
		if (LessonInterface)
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여하실수 있습니다."), *Person->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s님은 수업에 참여하실수 없습니다."), *Person->GetName());
		}
	}

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	// 학생/선생님 객체 생성.
	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();

	// 학생 클래스의 Getter 사용
	Student->SetName(TEXT("학생01"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름: %s"), *Student->GetName());

	// 언리얼의 리플렉션 시스템을 활용해서 프로퍼티 정보 가져오기
	FString CurrentTeacherName;
	FProperty* NameProperty = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProperty)
	{
		NameProperty->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름: %s"), *CurrentTeacherName);

		// 새로운 이름 설정
		FString NewTeacherName(TEXT("NewTeacherName"));
		NameProperty->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름: %s"), *Teacher->GetName());
	}

	// 함수 호출
	//Student->DoLesson();

	// 리플렉션을 통한 호출
	UFunction* DoLessonFunction = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));

	if (DoLessonFunction)
	{
		Teacher->ProcessEvent(DoLessonFunction, nullptr);
	}

	// 인터페이스 구현 여부에 따른 수업 참여 구분
	// 구현 여부를 확인하는 방법 -> 해당 인터페이스 형변환(다운 캐스팅)

	// 구성원의 카드 타입 출력
	for (const auto Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		ensure(OwnCard);

		//OwnCard->GetCardType();

		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/Unreal02_CppBasic.ECardType"));
		if (CardEnumType)
		{
			// GetDisplayNameTextByValue 함수는 FText를 반환함
			// FString으로 변환할 때는 ToString 함수 사용
			FString CardMetaData = CardEnumType->GetDisplayNameTextByValue((int64)OwnCard->GetCardType()).ToString();

			UE_LOG(LogTemp, Log, TEXT("%s님이 소유한 카드 종류: %s"), *Person->GetName(), *CardMetaData);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("============================================"));
}
