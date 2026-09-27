#pragma once
#include <iostream>
#include <math.h>
class vec3
{
public:
	float x;
	float y;
	float z;
	vec3();
	vec3(const float x, const float y, const float z);
	vec3(const vec3& v);
	vec3& operator=(const vec3& rhs);
	vec3 operator-() const;
	const vec3 operator+(const vec3& rhs);
	vec3& operator+=(const vec3& rhs);
	vec3 operator-(const vec3& rhs)const;
	vec3& operator-=(const vec3& rhs);
	vec3& operator*=(const float scalar);
	const vec3 operator*(const float scalar);
	const bool operator==(const vec3& rhs);
	const bool operator!=(const vec3& rhs);
	float& operator[](const unsigned int i); //range [0,2]
	const float& operator[](const unsigned int i)const; //range [0,2]
private:


};
//makes a empty vector
inline vec3::vec3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
//makes a vector with the numbers sent in
inline vec3::vec3(const float x, const float y, const float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
//makes a new vector the same as the one sent in
inline vec3::vec3(const vec3& v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}
//makes a vector the same as another vector 
inline vec3 &vec3::operator=(const vec3& rhs) {

	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}
//makes a vectors elements the opposite of what they where ex +10 becomes -10
inline vec3 vec3::operator-() const {
	float a = (this->x) * -1;
	float b= (this->y) * -1;
	float c= (this->z) * -1;
	return vec3(a, b, c);
}
//adds a vector from another vector and returns the new vector
inline vec3 const vec3::operator+(const vec3& rhs) {
	return vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}
//adds one vector to another and changes the value in the first vector
inline vec3& vec3::operator+=(const vec3& rhs) {
	this->x = this->x + rhs.x;
	this->y = this->y + rhs.y;
	this->z = this->z + rhs.z;
	return *this;
}
//subtracts a vector from another vector and returns the new vector
inline vec3 vec3::operator-(const vec3& rhs)const {
	return vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}
//subtracts one vector from another and changes the value in the first vector
inline vec3 &vec3::operator-=(const vec3& rhs) {
	this->x = this->x - rhs.x;
	this->y = this->y - rhs.y;
	this->z = this->z - rhs.z;
	return *this;
}
//multiplies a scalar and vector and changes the value in the vector
inline vec3 &vec3::operator*=(const float scalar) {
	this->x = this->x * scalar;
	this->y = this->y * scalar;
	this->z = this->z * scalar;
	return *this;
}
//multiplies a vector with a number(scalar)
inline vec3 const vec3::operator*(const float scalar) {
	return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}

//checks if two vectors are the same
inline bool const vec3::operator==(const vec3& rhs) {
	if (this->x == rhs.x) {
		if (this->y == rhs.y) {
			if (this->z == rhs.z) {
				return true;
			}
		}
	}

	return false;
	
}
//checks if two vectors are not the same
inline bool const vec3::operator!=(const vec3& rhs) {
	if (this->x == rhs.x) {
		if (this->y == rhs.y) {
			if (this->z == rhs.z) {
				return !true;
			}
		}
	}
	return true;
	
	
}
//returns the desired index of the vector in the range [0,2]
inline float& vec3::operator[](const unsigned int i) {
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

	default:
		break;
	}
}
//returns the desired index of the vector in the range [0,2]
inline const float& vec3::operator[](const unsigned int i)const {
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

	default:
		break;
	}
}
//dot product of two vectors
inline float dot(const vec3& a, const vec3& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z); 
}
//cross product of two vectors
inline vec3 cross(const vec3& a, const vec3& b) {
	float x = a.y * b.z - a.z * b.y; 
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	return vec3(x, y, z);
}
//returns the length of the vector
inline float length(const vec3& v) {
	float x = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return x;
}
//normalizes the vector
inline vec3 normalize(const vec3& v) {
	float len = length(v);
	float X = v.x / len;
	float Y = v.y / len;
	float Z = v.z / len;
	return vec3(float(X), float(Y), float(Z));
}


