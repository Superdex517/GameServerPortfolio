#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"

GameSessionManager GSessionManager;

void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.insert(session);
}

void GameSessionManager::Remove(GameSessionRef session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}

//���⼭ ������ ���� �Ͼ
void GameSessionManager::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	//���ʿ��� ���簡 �������

	//for���� ������ ��� ��ȭ�� �Ͼ�� �����Ͱ� �����ǰ� �� -> ũ���� �߻�
	for (GameSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}
