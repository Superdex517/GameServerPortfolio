#pragma once
#include <stack>

//ǥ�ؿ��� ������ �߱��������� id�� �Ҵ�Ǳ� ������ �������
//���߱� ���� ���� ���� 
extern thread_local uint32 LThreadId;

extern thread_local std::stack<int32> LLockStack;

