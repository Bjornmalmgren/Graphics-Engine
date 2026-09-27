#pragma once
#include <math.h>
class vec4
{
public:
	float x;
	float y;
	float z;
	float w;
	vec4();
	vec4(const float x, float const y, float const z, float const w);
	vec4(const vec4& v);
	vec4& operator=(const vec4& rhs);
	const vec4 operator-();
	const vec4 operator+(const vec4& rhs);
	vec4& operator+=(const vec4& rhs);
	const vec4 operator-(const vec4& rhs);
	vec4& operator-=(const vec4& rhs);
	vec4& operator*=(const float scalar);
	const vec4 operator*(const float scalar);
	const bool operator==(const vec4& rhs);
	const bool operator!=(const vec4& rhs);
	float& operator[](const unsigned int i); //range [0,2]
	const float& operator[](const unsigned int i)const; //range [0,2

private:

};
//makes a empty vector
inline vec4::vec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}
//makes a vector with the numbers sent in
inline vec4::vec4(const float x, float const y, float const z, float const w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
//makes a new vector the same as the one sent in
inline vec4::vec4(const vec4& v){
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}
//makes a vector the same as another vector 
inline vec4& vec4::operator=(const vec4& rhs) {

	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
	return *this;
}
//makes a vectors elements the opposite of what they where ex +10 becomes -10
inline vec4 const vec4::operator-() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
	this->w = -this->w;
	return vec4(this->x, this->y, this->z, this->w);
}
//adds a vector from another vector and returns the new vector
inline vec4 const vec4::operator+(const vec4& rhs) {
	return vec4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
}
//adds one vector to another and changes the value in the first vector
inline vec4& vec4::operator+=(const vec4& rhs) {
	this->x = this->x + rhs.x;
	this->y = this->y + rhs.y;
	this->z = this->z + rhs.z;
	this->w = this->w + rhs.w;
	return *this;
}
//subtracts a vector from another vector and returns the new vector
inline vec4 const vec4::operator-(const vec4& rhs) {
	return vec4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
}
//subtracts one vector from another and changes the value in the first vector
inline vec4& vec4::operator-=(const vec4& rhs) {
	this->x = this->x - rhs.x;
	this->y = this->y - rhs.y;
	this->z = this->z - rhs.z;
	this->w = this->w - rhs.w;
	return *this;
}
//multiplies a scalar and vector and changes the value in the vector
inline vec4& vec4::operator*=(const float scalar) {
	this->x = this->x * scalar;
	this->y = this->y * scalar;
	this->z = this->z * scalar;
	this->w = this->w * scalar;
	return *this;
}
//multiplies a vector with a number(scalar)
inline vec4 const vec4::operator*(const float scalar) {
	return vec4(this->x * scalar, this->y * scalar, this->z * scalar, this->w * scalar);
}
//checks if two vectors are the same
inline bool const vec4::operator==(const vec4& rhs) {
	if (this->x == rhs.x) {
		if (this->y == rhs.y) {
			if (this->z == rhs.z) {
				if (this->w == rhs.w) {
					return true;
				}
			}
		}
	}
	return false;
	

}
//checks if two vectors are not the same
inline bool const vec4::operator!=(const vec4& rhs) {
	if (this->x == rhs.x) {
		if (this->y == rhs.y) {
			if (this->z == rhs.z) {
				if (this->w == rhs.w) {
					return false;
				}
			}
		}
	}
	return true;
	

}
//returns the desired index of the vector in the range [0,3]
inline float& vec4::operator[](const unsigned int i) {
	switch (i)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;

	default:
		break;
	}
}
//returns the desired index of the vector in the range [0,3]
inline const float& vec4::operator[](const unsigned int i)const {
	switch (i)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;

	default:
		break;
	}
}
//dot product of two vectors
inline float dot(const vec4& a, const vec4& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w*b.w);
}
//returns the length of the vector
inline float length(const vec4& v) {
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w*v.w)));
}
//normalizes the vector
inline vec4 normalize(const vec4& v) {
	float len = length(v);
	float X = v.x / len;
	float Y = v.y / len;
	float Z = v.z / len;
	float W = v.w / len;
	return vec4(float(X), float(Y), float(Z), float(W));
}
