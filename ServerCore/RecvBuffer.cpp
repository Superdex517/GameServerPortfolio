#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize) : _bufferSize(bufferSize) 
{
	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	int32 dataSize = DataSize();
	if (dataSize == 0)
	{
		//딱 마침 읽기쓰기 커서가 동일한 위치라면 둘 다 리셋
		_readPos = _writePos = 0;
	}
	else
	{
		//[][][][][][][][][][r][][w] -> 해당 경우에는 앞으로 복사해줘야함
		//여유 공간이 버퍼 1개 크기 미만이면, 데이터를 앞으로 땅긴다
		if (FreeSize() < _bufferSize)
		{
			::memcpy(&_buffer[0], &_buffer[_readPos], dataSize);
			_readPos = 0;
			_writePos = dataSize;
			//복사비용을 아끼려면??
			//rw가 언젠간 같은 위치에 올 수 있도록 버퍼의 사이즈를 늘려놓는다
		}
	}
}

bool RecvBuffer::OnRead(int32 numOfBytes)
{
	if (numOfBytes > DataSize())
		return false;

	_readPos += numOfBytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 numOfBytes)
{
	if (numOfBytes > FreeSize())
		return false;

	_writePos += numOfBytes;
	return true;
}
