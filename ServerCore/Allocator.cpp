#include "pch.h"
#include "Allocator.h"
#include "Memory.h"

void* BaseAllocator::Alloc(int32 size)
{
	return ::malloc(size);
}

void BaseAllocator::Release(void* ptr)
{
	::free(ptr);
}

// 개발 단계에서 메모리 오염 버그를 예방해줌
// [[xxxx]x         ] -> 이렇게 초과된 메모리때문에 오류가 발생하는데
// 개발단계에서 해당 경우를 잡아줌
// stompalloc을 [                  [xxxx]] 이렇게 배치해줌
void* StompAllocator::Alloc(int32 size)
{
	const int64 pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;
	const int64 dataOffset = pageCount * PAGE_SIZE - size;

	void* baseAddress = ::VirtualAlloc(NULL, pageCount * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	return static_cast<void*>(static_cast<int8*>(baseAddress) + dataOffset);
}

// 메모리를 해제할때 초기 위치를 맨 앞으로(페이지의 초기 위치) 되돌려준다.
void StompAllocator::Release(void* ptr)
{
	const int64 address = reinterpret_cast<int64>(ptr);
	const int64 baseAddress = address - (address % PAGE_SIZE);
	::VirtualFree(reinterpret_cast<void*>(baseAddress), 0, MEM_RELEASE);
}


//다른 클래스라고 해도 크기만 같은면 같은 pool에서 관리한다
void* PoolAllocator::Alloc(int32 size)
{

	return GMemory->Allocate(size);
}

void PoolAllocator::Release(void* ptr)
{
	GMemory->Release(ptr);
}
