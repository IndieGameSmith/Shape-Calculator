#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

#include <iostream>

struct vector2f
{
	vector2f(float p_x = 0.0f, float p_y = 0.0f) : x(p_x), y(p_y) {};
	vector2f& operator+(const vector2f& other);
	vector2f& operator-(const vector2f& other);
	vector2f& operator*(float scaler);
	vector2f& operator/(float scaler);
	bool operator==(const vector2f& other);
	bool operator!=(const vector2f& other);
	float dot(const vector2f& other);
	float magnitude() const;
	vector2f& normalize();
	
	
	float x, y;
	
private:
	float Tolerance_value = 0.001f;
};


std::ostream& operator<<( std::ostream& str, const vector2f& v);

#endif
