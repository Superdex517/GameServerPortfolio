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

// ���� �ܰ迡�� �޸� ���� ���׸� ��������
// [[xxxx]x         ] -> �̷��� �ʰ��� �޸𸮶����� ������ �߻��ϴµ�
// ���ߴܰ迡�� �ش� ��츦 �����
// stompalloc�� [                  [xxxx]] �̷��� ��ġ����
void* StompAllocator::Alloc(int32 size)
{
	const int64 pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;
	const int64 dataOffset = pageCount * PAGE_SIZE - size;

	void* baseAddress = ::VirtualAlloc(NULL, pageCount * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	return static_cast<void*>(static_cast<int8*>(baseAddress) + dataOffset);
}

// �޸𸮸� �����Ҷ� �ʱ� ��ġ�� �� ������(�������� �ʱ� ��ġ) �ǵ����ش�.
void StompAllocator::Release(void* ptr)
{
	const int64 address = reinterpret_cast<int64>(ptr);
	const int64 baseAddress = address - (address % PAGE_SIZE);
	::VirtualFree(reinterpret_cast<void*>(baseAddress), 0, MEM_RELEASE);
}


//�ٸ� Ŭ������� �ص� ũ�⸸ ������ ���� pool���� �����Ѵ�
void* PoolAllocator::Alloc(int32 size)
{

	return GMemory->Allocate(size);
}

void PoolAllocator::Release(void* ptr)
{
	GMemory->Release(ptr);
}
