#pragma once

class BufferWriter
{
public:
	BufferWriter();
	BufferWriter(BYTE* buffer, uint32 size, uint32 pos = 0);
	~BufferWriter();

	BYTE* Buffer() { return _buffer; }
	uint32 Size() { return _size; }
	uint32 WriteSize() { return _pos; }
	uint32 FreeSize() { return _size - _pos; }


	template<typename T>
	bool Write(T* src) { return Read(src, sizeof(T)); }
	bool Write(void* src, uint32 len);

	template<typename T>
	T* Reserve(uint16 count = 1);

	template<typename T>
	BufferWriter& operator<<(T&& src);

private:
	BYTE* _buffer = nullptr;
	uint32 _size = 0;
	uint32 _pos = 0;
};

template<typename T>
T* BufferWriter::Reserve(uint16 count)
{
	if (FreeSize() < (sizeof(T) * count))
		return nullptr;

	//버퍼의 포인터 주소
	T* ret = reinterpret_cast<T*>(&_buffer[_pos]);
	_pos += (sizeof(T) * count);
	return ret;
}

//오른값 참조
template<typename T>
BufferWriter& BufferWriter::operator<<(T&& src)
{
	//데이터 타입 추출
	using DataType = std::remove_reference_t<T>;

	*reinterpret_cast<DataType*>(&_buffer[_pos]) = std::forward<DataType>(src);
	_pos += sizeof(T);
	return *this;
}