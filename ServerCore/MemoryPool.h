#pragma once
enum
{
	SLIST_ALIGNMENT = 16,
};

DECLSPEC_ALIGN(SLIST_ALIGNMENT)
struct MemoryHeader : public SLIST_ENTRY
{
	MemoryHeader(int32 size) : allocSize(size) { }
	
	//메모리를 받아서 헤더에 사이즈 기입
	static void* AttachHeader(MemoryHeader* header, int32 size)
	{
		new(header)MemoryHeader(size);
		return reinterpret_cast<void*>(++header);
	}
	
	//메모리를 다 사용하면 헤더를 추출
	static MemoryHeader* DetachHeader(void* ptr)
	{
		MemoryHeader* header = reinterpret_cast<MemoryHeader*>(ptr) - 1;
		return header;
	}

	int32 allocSize;
};

DECLSPEC_ALIGN(SLIST_ALIGNMENT)
class MemoryPool
{
public:
	MemoryPool(int32 allocSize);
	~MemoryPool();

	void Push(MemoryHeader* ptr);
	MemoryHeader* Pop();
private:
	//첫번째 노드
	SLIST_HEADER _header;
	int32 _allocSize = 0;
	atomic<int32> _useCount = 0;
	atomic<int32> _reserveCount = 0;
};

