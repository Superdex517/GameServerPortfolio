#pragma once


//순환버퍼 사용이 가장 정석적인 방법
class RecvBuffer
{
	//	RecvBuffer(int32 buffersize)의 버퍼보다 10배 더 크게
	enum { BUFFER_COUNT = 10 };
public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();

	void Clean();
	bool OnRead(int32 numOfBytes);
	bool OnWrite(int32 numOfBytes);

	BYTE* ReadPos() { return &_buffer[_readPos]; }
	BYTE* WritePos() { return &_buffer[_writePos]; }

	//유효한 데이터 사이즈(실질적으로 사용하고 있는 데이터 크기)
	int32 DataSize() { return _writePos - _readPos; }
	//사용 가능한 공간
	int32 FreeSize() { return _capacity - _writePos; }

private:
	int32 _capacity = 0; //진짜 데이터 사이즈
	int32 _bufferSize = 0;
	int32 _readPos = 0;
	int32 _writePos = 0;
	Vector<BYTE> _buffer;
};

