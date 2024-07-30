#include "pch.h"
#include "SocketUtils.h"

LPFN_CONNECTEX SocketUtils::ConnectEx = nullptr;
LPFN_DISCONNECTEX SocketUtils::DisconnectEx = nullptr;
LPFN_ACCEPTEX SocketUtils::AcceptEx = nullptr;

void SocketUtils::Init()
{
	WSADATA wsaData;
	::WSAStartup(MAKEWORD(2, 2), OUT & wsaData);
}

void SocketUtils::Clear()
{
}
