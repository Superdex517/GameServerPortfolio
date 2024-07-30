#pragma once

#define OUT
/**************
	LOCK
**************/
#define USE_MANY_LOCKS(count)			Lock _lock[count];
#define USE_LOCK						USE_MANY_LOCKS(1);
#define READ_LOCK_IDX(idx)				ReadLockGuard readLockGuard_##idx(_locks[idx], typeid(this).name());
#define READ_LOCK						READ_LOCK_IDX(0);
#define WRITE_LOCK_IDX(idx)				WriteLockGuard writeLockGuard_##idx(_locks[idx], typeid(this).name());
#define WRITE_LOCK						WRITE_LOCK_IDX(0);


// 컴파일 단계에서 오류를 잡아버릴 경우도 있음
// 인위적인 크래쉬를 위한 함수
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}

// 조건부로 크래쉬 내는 상황
#define ASSERT_CRASH(expr)						\
{												\
	if(!(expr))									\
	{											\
		CRASH("ASSERT_CRASH");					\
		__analysis_assume(crash != nullptr);	\
	}											\
}