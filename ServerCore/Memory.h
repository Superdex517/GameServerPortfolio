#pragma once
#include "Allocator.h"

class MemoryPool;

class Memory
{
	enum
	{
		POOL_COUNT = (1024 / 32) + (1024 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
	};

public:
	Memory();
	~Memory();

	void* Allocate(int32 size);
	void Release(void* ptr);

private:
	vector<MemoryPool*> _pools;

	//메모리 크기에 따라 메모리 풀을 찾음
	//0(1) 빠르게 찾기 위한 테이블
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename Type, typename... Args>
Type* Xnew(Args&&... args)
{
	//메모리 할당
	Type* memory = static_cast<Type*>(PoolAllocator::Alloc(sizeof(Type)));
	
	//메모리 위에 생성자를 호출해달라는 문법
	new(memory)Type(std::forward<Args>(args)...);
	return memory;
}

template<typename Type>
void Xdelete(Type* obj)
{
	obj->~Type();
	PoolAllocator::Release(obj);
}

template<typename Type>
shared_ptr<Type> MakeShared()
{
	return shared_ptr<Type>{ Xnew<Type>(), Xdelete<Type>};
}