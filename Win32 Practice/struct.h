#pragma once
#include <cassert>

struct Vec2 // 정수 값을 가진 물체를 움직이면 너무 빠르기 때문에 float값을 사용하기 위해 struct 선언
{
	float x;
	float y;

public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fLen = Length();

		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}

 	Vec2& operator = (POINT _pt)
 	{
 		x = (float)_pt.x;
 		y = (float)_pt.y;
		
		return *this;
 	}

	Vec2 operator + (Vec2 _vec)
	{
		Vec2 tmp;

		tmp.x = x + _vec.x;
		tmp.y = y + _vec.y;

		return tmp;
	}

	Vec2 operator + (float _f)
	{
		Vec2 tmp;

		tmp.x = x + _f;
		tmp.y = y + _f;

		return tmp;
	}

	Vec2 operator - (Vec2 _vec)
	{
		Vec2 tmp;

		tmp.x = x - _vec.x;
		tmp.y = y - _vec.y;

		return tmp;
	}

	Vec2 operator * (Vec2 _vec)
	{
		Vec2 tmp;

		tmp.x = x * _vec.x;
		tmp.y = y * _vec.y;

		return tmp;
	}

	Vec2 operator / (Vec2 _vec)
	{
		assert(_vec.x == 0 || _vec.y == 0);

		Vec2 tmp;

		tmp.x = x / _vec.x;
		tmp.y = y / _vec.y;

		return tmp;
	}

	Vec2 operator / (float _f)
	{
		assert(!(0.f == _f));
		return Vec2(x / _f, y / _f);
	}

	Vec2 operator * (float _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

public:
	Vec2()
		:x(0.f)
		, y(0.f)//생성자 다음 : 은 초기화 해주는 방법중 하나
	{}

	Vec2(float _x, float _y)
		:x(_x)
		,y(_y)
	{}

	Vec2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		:x((float)_pt.x)
		,y((float)_pt.y)
	{}

};