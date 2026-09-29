#include "StudentManager.h"
#include "Student.h"

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	// 객체가 유효한지 확인
	if (SafeStudent->IsValidLowLevel())
	{
		// 메모리 관리되도록 등록
		Collector.AddReferencedObject(SafeStudent);
	}
}
