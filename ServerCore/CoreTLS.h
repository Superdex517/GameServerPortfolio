#pragma once
#include <stack>

//표준에도 있지만 중구난방으로 id가 할당되기 때문에 순서대로
//맞추기 위해 직접 생성 
extern thread_local uint32 LThreadId;

extern thread_local std::stack<int32> LLockStack;

