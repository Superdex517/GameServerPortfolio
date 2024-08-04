#include "pch.h"
#include <iostream>
#include <mutex>
#include <atomic>
#include <future>
#include "ThreadManager.h"

#include "RefCounting.h"
#include "Memory.h"
#include "Allocator.h"

#include "SocketUtils.h"

int main()
{
	SOCKET socket = SocketUtils::CreateSocket();

	SocketUtils::BindAnyAddress(socket, 7777);

	SocketUtils::Listen(socket);

	SOCKET clientSocket = ::accept(socket, nullptr, nullptr);

	cout << "Client connected" << endl;

	while (true)
	{

	}
	GThreadManager->Join();
}
