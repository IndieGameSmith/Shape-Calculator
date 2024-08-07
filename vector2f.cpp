#include <cmath>
#include "/storage/emulated/0/Android/C++ Programmes /Shape Calculator/include/GUI/Utilities/vector2f.hpp"

#ifndef VECTOR2F_CPP_
#define VECTOR2F_CPP_

vector2f& vector2f :: operator+(const vector2f& other)
{
	x += other.x;
	y += other.y;
	
	return *this;
}

vector2f& vector2f :: operator-(const vector2f& other)
{
	x -= other.x;
	y -= other.y;
	
	return *this;
}

vector2f& vector2f :: operator*(float scaler)
{
	x *= scaler;
	y *= scaler;
	
	return *this;
}

vector2f& vector2f :: operator/(float scaler)
{
	if (scaler == 0)
		throw std::runtime_error("Can't be divided by 0");
	
	x *= scaler;
	y *= scaler;
	
	return *this;
}

float vector2f :: magnitude() const
{
	return std::sqrt(x * x + y * y);
}

vector2f& vector2f :: normalize()
{
	float mag = magnitude();
	
	if (std::abs(mag) < Tolerance_value)
	{
		x = y = 0.0f;
	}
	x /= mag;
	y /= mag;
	return *this;
}

std::ostream& operator<<( std::ostream& str, const vector2f& v)
{
	str << "[" << v.x << ", " << v.y << "]";
	return str;
}

#endif