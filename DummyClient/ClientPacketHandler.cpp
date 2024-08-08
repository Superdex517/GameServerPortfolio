#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	}
}

struct BuffData
{
	uint64 buffId;
	float remainTime;
};

struct S_TEST
{
	uint64 id;
	uint32 hp;
	uint16 attack;

	//���������� �߰��Ǹ�??
	//1) ���ڿ�
	//2) �׳� ����Ʈ �迭(��� �̹���)
	//3) �Ϲ� ����Ʈ
	vector<BuffData> buffs;

	wstring name;
};

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	uint64 id;
	uint32 hp;
	uint16 attack;
	br >> id >> hp >> attack;

	cout << " ID: " << id << " HP : " << hp << " attack:  " << attack << endl;

	vector<BuffData> buffs;
	uint16 buffCount;
	br >> buffCount;

	buffs.resize(buffCount);
	for (BuffData& i : buffs)
	{
		br >> i.buffId >> i.remainTime;
	}

	cout << "BuffCount : " << buffCount << endl;
	for (BuffData& i : buffs)
	{
		cout << "BufInfo : " << i.buffId << " " << i.remainTime << endl;
	}

	wstring name;
	uint16 nameLen;
	br >> nameLen;
	name.resize(nameLen);

	br.Read((void*)name.data(), nameLen * sizeof(WCHAR));

	wcout.imbue(std::locale("kor"));
	wcout << name << endl;
}
