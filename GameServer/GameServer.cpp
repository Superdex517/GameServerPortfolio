﻿#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ServerPacketHandler.h"

int main()
{
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	//사이즈 입력 조심!!
	WCHAR sendData[1000] = L"Hello World";

	//bufferWrite, reader는 복잡하게 사용했던 패킷을 보기 편하게 만들어준것
	while (true)
	{
		vector<BuffData> buffs{ BuffData{100, 1.5f}, BuffData{200, 2.5f}, BuffData{300, 0.7f}, };
		SendBufferRef sendBuffer = ServerPacketHandler::Make_S_TEST(1001, 100, 10, buffs, L"안녕");

		GSessionManager.Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}

	GThreadManager->Join();
}