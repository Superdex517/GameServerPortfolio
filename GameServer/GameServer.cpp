#include "pch.h"
#include <iostream>
#include <mutex>
#include <atomic>
#include <future>
#include "ThreadManager.h"
#include "RefCounting.h"


class Wraight : public RefCountable
{
public:
	int _hp = 150;
	int _posX = 0;
	int _posY = 0;
};
using WraightRef = TSharedPtr<Wraight>;

class Missile : public RefCountable
{
public:
	void SetTarget(WraightRef target)
	{
		_target = target;
		//중간에 누군가 개입 가능
		//Test(target);
	}

	//진짜 내부적으로 사용하게 될 경우 
	//스마트 포인터의 레퍼런스를 넘겨주는방식으로 사용
	//void Test(WraightRef& target)
	//{

	//}

	bool Update()
	{
		if (_target == nullptr)
			return true;

		int posX = _target->_posX;
		int posY = _target->_posY;

		if (_target->_hp == 0)
		{
			_target->ReleaseRef();
			_target = nullptr;
			return true;
		}

		return false;
	}

	WraightRef _target = nullptr;
};
using MissileRef = TSharedPtr<Missile>;

int main()
{
	WraightRef w(new Wraight());
	w->ReleaseRef();
	MissileRef m(new Missile());
	m->ReleaseRef();

	m->SetTarget(w);
	w->_hp = 0;
	w = nullptr;

	while (true)
	{
		if (m->Update())
		{
			m = nullptr;
		}
	}
	m = nullptr;
}
