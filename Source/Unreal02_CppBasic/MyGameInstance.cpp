// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"
#include "StudentManager.h"
#include "MyObject.h"
#include <Algo/Accumulate.h>
#include <JsonObjectConverter.h>

// 이름 값을 랜덤으로 생성하는 함수
FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandArray;

	// 세 글자로 이름을 만들기 위해 3개의 공간 확보
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	// 이름 문자열로 변환해서 반환
	return RandArray.GetData();
}

void CheckUObjectIsValid(const UObject* InObject, const FString& InTag)
{
	if (InObject->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효한 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] 유효하지 않은 언리얼 오브젝트"), *InTag);
	}
}

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag)
{
	if (nullptr == InObject)
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] nullptr 언리얼 오브젝트"), *InTag);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[%s] nullptr이 아닌 언리얼 오브젝트"), *InTag);
	}
}

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

	// 학사 정보 객체 생성
	CourseInfo = NewObject<UCourseInfo>(this);

	// 3개의 학생 객체 생성
	UStudent* Student01 = NewObject<UStudent>();
	Student01->SetName(TEXT("학생01"));

	UStudent* Student02 = NewObject<UStudent>();
	Student02->SetName(TEXT("학생02"));

	UStudent* Student03 = NewObject<UStudent>();
	Student03->SetName(TEXT("학생03"));

	// 학사 정보 객체와 학생 객체의 연결
	// 발생 주체와 구독 주체의 연결 (의존성을 피할 수 없는 부분)
	// MyGameInstance는 일종의 관리자(Manager) 성격의 객체

	// 구독 처리
	CourseInfo->OnChanged.AddUObject(Student01, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student02, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student03, &UStudent::GetNotification);

	// 변경된 학사 정보 발행
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	// 간단한 TArray 사용 예제
	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Array.Add(ix);
	}

	Int32Array.RemoveAll([](int32 val) { return val % 2 == 0; });

	Int32Array += {2, 4, 6, 8, 10};

	// 두 번째 배열 선언
	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1,3,5,7,9,2,4,6,8,10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum);

	// 두 배열이 같은지 확인
	ensure(Int32Array == Int32ArrayCompare);

	// 일반적인 합계 구하는 방법
	int32 Sum = 0;
	for (const int32& Int32Num : Int32Array)
	{
		Sum += Int32Num;
	}

	// 알고리즘 활용 (합계 구하기)
	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);

	// TSet 예제
	TSet<int32> Int32Set;


	// 데이터 추가
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Set.Add(ix);
	}

	// 제거
	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	// 추가
	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	// 학생 데이터 생성
	const int32 StudentNum = 300;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentData.Emplace(FStudentData(MakeRandomName(), ix));
	}

	// 학생 데이터를 TArray<FString> 배열로 변환
	TArray<FString> AllStudentsNames;
	Algo::Transform(StudentData, AllStudentsNames, [](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	// 배열 요소 수 출력
	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수: %d"), AllStudentsNames.Num());

	// 학생의 이름을 Set에 저장
	// Set은 중복을 허락하지 않음 Key가 곧 Value
	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentData, AllUniqueNames, [](const FStudentData& Val)
		{
			return Val.Name;
		}
	);
	UE_LOG(LogTemp, Log, TEXT("중복없는 학생 이름의 수: %d"), AllUniqueNames.Num());

	// 학생 데이터를 Map으로 변환
	Algo::Transform(StudentData, StudentsMap, [](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수: %d"), StudentsMap.Num());

	// 이름(문자열)을 키로 사용하는 맵 선언
	TMap<FString, int32> StudentsMapByUniqueName;

	// 학생 데이터를 Map으로 변환
	Algo::Transform(StudentData, StudentsMapByUniqueName, [](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수: %d"), StudentsMapByUniqueName.Num());

	TMultiMap<FString, int32> StudentsMapByName;

	// 학생 데이터를 Map으로 변환
	Algo::Transform(StudentData, StudentsMapByName, [](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);
	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 멀티맵의 레코드 수: %d"), StudentsMapByName.Num());

	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수: %d"), *TargetName, AllOrders.Num());

	// 테스트
	TSet<FStudentData> StudentsSet;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), ix));
	}
	UE_LOG(LogTemp, Log, TEXT("학생 데이터 셋에 저장된 데이터 수: %d"), StudentsSet.Num());

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	NonPropStudent = NewObject<UStudent>();
	PropStudent = NewObject<UStudent>();

	NonPropStudents.Add(NewObject<UStudent>());
	PropStudents.Add(NewObject<UStudent>());

	// StudentManager 객체 생성
	StudentManager = new FStudentManager(NewObject<UStudent>());

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	// 객체 생성
	FStudentData RawDataSource(TEXT("ㅇㅣㄹㅡㅁ"), 123);

	// 파일로 다루기 위해 경로 설정
	const FString SavedPath = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));

	// 경로 출력
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더: %s"), *SavedPath);

	// 직렬화 구간
	{
		// 저장할 파일 이름
		const FString RawDataFileName(TEXT("RawData.bin"));

		// 파일 이름을 포함한 최종 경로
		FString RawDataAbsolutePath = FPaths::Combine(SavedPath, RawDataFileName);

		// 경로 출력 (테스트)
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로: %s"), *RawDataAbsolutePath);

		// 경로 정리
		FPaths::MakeStandardFilename(RawDataAbsolutePath);

		// 변경된 경로 출력
		UE_LOG(LogTemp, Log, TEXT("변경된 파일 전체 경로: %s"), *RawDataAbsolutePath);

		/* 오브젝트 직렬화
		// 1. 직렬화 처리를 위한 아카이브 생성
		FArchive* RawFileWriteAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (RawFileWriteAr)
		{
			// 2. 아카이브에 오브젝트 직렬화
			*RawFileWriteAr << RawDataSource;

			// 파일 닫기
			RawFileWriteAr->Close();

			// 사용한 리소스 해제
			delete RawFileWriteAr;
			RawFileWriteAr = nullptr;
		}	//*/

		// 오브젝트 역직렬화
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);

		// 파일로부터 데이터를 복원할 객체
		FStudentData RawDataDeserialized;

		if (RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDeserialized;

			// 파일 닫기
			RawFileReaderAr->Close();

			// 해제
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			// 로드한 데이터 출력
			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름: %s, 순번: %d"), *RawDataDeserialized.Name, RawDataDeserialized.Order);
		}

	}	

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	//* 언리얼 오브젝트 직렬화
	StudentSrc = NewObject<UMyObject>();
	StudentSrc->SetOrder(100);
	StudentSrc->SetName(TEXT("Unreal오브젝트직렬화"));
	{
		// 파일 이름
		const FString& ObjectDataFileName(TEXT("ObjectData.bin"));

		// 최종 경로 설정
		FString ObjectDataPath = FPaths::Combine(SavedPath, ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataPath);

		// 직렬화
		// 1. 메모리 직렬화
		TArray<uint8> Buffer;
		FMemoryWriter MemoryWriter(Buffer);
		
		// 오브젝트 직렬화
		StudentSrc->Serialize(MemoryWriter);

		// 2. 파일에 기록
		TUniquePtr<FArchive> FileWriter = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataPath));

		if (FileWriter)
		{
			// 기록
			*FileWriter << Buffer;

			// 파일 닫기
			FileWriter->Close();
		}

		//* 역직렬화
		// 1. 파일 로드 -> 바이트 배열
		TArray<uint8> BufferFromFile;
		TUniquePtr<FArchive> FileReader = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataPath));

		if (FileReader)
		{
			// 파일에 로드한 데이터를 바이트 배열에 저장
			*FileReader << BufferFromFile;

			// 파일 닫기
			FileReader->Close();

			// 2. 바이트 배열 -> 오브젝트로 복원
			FMemoryReader MemoryReader(BufferFromFile);

			// 테스트를 위한 임시 객체 생성
			UMyObject* NewStudent = NewObject<UMyObject>();
			NewStudent->Serialize(MemoryReader);

			// 로드한 데이터 출력
			UE_LOG(LogTemp, Log, TEXT("[Ureal ObjectData] 이름: %s, 순번: %d"), *NewStudent->GetName(),NewStudent->GetOrder());
		}
	}	//*/

	UE_LOG(LogTemp, Log, TEXT("============================================"));

	// Json 직렬화
	{
		// Object -> Json Object -> Json 문자열 -> 파일로 기록

		// 파일 이름
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));

		// 경로
		FString JsonDataPath = FPaths::Combine(SavedPath, JsonDataFileName);

		// 경로 정리
		FPaths::MakeStandardFilename(JsonDataPath);

		// JsonObject 공유 레퍼런스 객체 생성
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

		// 언리얼 오브젝트 -> Json 오브젝트
		FJsonObjectConverter::UStructToJsonObject(
			StudentSrc->GetClass(),
			StudentSrc,
			JsonObject
		);

		// JsonObject -> Json 문자열
		FString JsonString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter
			= TJsonWriterFactory<TCHAR>::Create(&JsonString);

		// 직렬화: JsonObject -> Json 문자열
		if (FJsonSerializer::Serialize(JsonObject, JsonWriter))
		{
			// Json 문자열 -> 파일로 기록
			FFileHelper::SaveStringToFile(JsonString, *JsonDataPath);
		}

		// 역직렬화
		// 파일 로드 -> Json 문자열 -> Json Object -> Object

		// 1. 파일 로드 -> Json 문자열
		FString JsonInString;
		FFileHelper::LoadFileToString(JsonInString, *JsonDataPath);

		// 2. Json 문자열 -> Json Object
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObjectDest;
		if (FJsonSerializer::Deserialize(JsonReader, JsonObjectDest))
		{
			UMyObject* JsonStudentDest = NewObject<UMyObject>();
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				UE_LOG(LogTemp, Log, TEXT("[JSon Unreal ObjectData] 이름: %s, 순번: %d"), *JsonStudentDest->GetName(), JsonStudentDest->GetOrder());
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("============================================"));
}

void UMyGameInstance::Shutdown()
{
	Super::Shutdown();

	const UStudent* StudentInManager = StudentManager->GetStudent();

	// 메모리 정리
	delete StudentManager;
	StudentManager = nullptr;

	CheckUObjectIsNull(StudentInManager, TEXT("StudentInManager"));
	CheckUObjectIsValid(StudentInManager, TEXT("StudentInManager"));

	CheckUObjectIsNull(NonPropStudent, TEXT("NonPropStudent"));
	CheckUObjectIsValid(NonPropStudent, TEXT("NonPropStudent"));

	CheckUObjectIsNull(PropStudent, TEXT("PropStudent"));
	CheckUObjectIsValid(PropStudent, TEXT("PropStudent"));

	CheckUObjectIsNull(NonPropStudents[0], TEXT("NonPropStudents"));
	CheckUObjectIsValid(NonPropStudents[0], TEXT("NonPropStudents"));

	CheckUObjectIsNull(PropStudents[0], TEXT("PropStudents"));
	CheckUObjectIsValid(PropStudents[0], TEXT("PropStudents"));
}
