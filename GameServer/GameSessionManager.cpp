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

//여기서 문제가 많이 일어남
void GameSessionManager::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	//불필요한 복사가 사라졌다

	//for문을 돌릴때 어떠한 변화가 일어나면 데이터가 오염되게 됨 -> 크래시 발생
	for (GameSessionRef session : _sessions)
	{
		session->Send(sendBuffer);
	}
}
