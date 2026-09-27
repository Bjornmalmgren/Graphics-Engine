#pragma once
#include <math.h>
#include "vec4.h"
#include "vec3.h"
class mat4
{
public:
	vec4 m[4];
	mat4(); 
	mat4(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3);
	mat4(const mat4& m);
	mat4& operator=(const mat4& rhs);
	mat4 operator*(const mat4& rhs)const;
	vec4 operator*(const vec4& rhs)const;
	bool operator==(const mat4& rhs)const;
	bool operator!=(const mat4& rhs)const;
	vec4& operator[](const unsigned int i);
	const vec4& operator[](const unsigned int i)const;
	mat4 lookat(const vec3& eye, const vec3& at, const vec3& up);
	mat4 perspective(const float fovy, const float aspect, const float near, const float far);
private:

};
//makes a indentity matrix
inline mat4::mat4()
{

	this->m[0] = vec4(1,0,0,0);
	this->m[1] = vec4(0,1,0,0);
	this->m[2] = vec4(0,0,1,0);
	this->m[3] = vec4(0,0,0,1);
}
//makes a matrix with the vectors sent in
inline mat4::mat4(const vec4& r0, const vec4& r1, const vec4& r2, const vec4& r3)
{
	this->m[0] = r0;
	this->m[1] = r1;
	this->m[2] = r2;
	this->m[3] = r3;
}
//makes a identical matrix from the one sent in
inline mat4::mat4(const mat4& m2)
{
	this->m[0] = m2[0];
	this->m[1] = m2[1];
	this->m[2] = m2[2];
	this->m[3] = m2[3];
}
//makes a matrix the same as another matrix
inline mat4 &mat4::operator=(const mat4& rhs) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = rhs[i][j];
		}
	}
	return *this;
}
//multiplies a matrix with a matrix (4x4 * 4x4)
inline mat4 mat4::operator*(const mat4& rhs)const {
	mat4 multipliedMatrix;
	for (int i = 0; i < 4; i++)
	{
		vec4 newMatrixRow;
		for (int j = 0; j < 4; j++)
		{
			//std::cout << " " << m[0][i] * rhs[j][0] << " " << m[i][1] * rhs[1][j] << " " << m[i][2] * rhs[2][j] << " " << m[i][3] * rhs[3][j] << std::endl;

			//newMatrixRow[j] = m[0][i] * rhs[j][0] + m[1][i] * rhs[j][1] + m[2][i] * rhs[j][2] + m[3][i] * rhs[j][3];
			newMatrixRow[j] = dot(vec4(m[0][j], m[1][j], m[2][j], m[3][j]),rhs[i]);
		}
		
		
		multipliedMatrix[i] = newMatrixRow;
	}
	return multipliedMatrix;
}
//multiples a vector with the matrix returning a vector (4x4 * 4x1)
inline vec4 mat4::operator*(const vec4& rhs)const {
	vec4 newMatrixRow;
	for (int i = 0; i < 4; i++)
	{

		newMatrixRow[i] = m[0][i] * rhs[0] + m[1][i] * rhs[1] + m[2][i] * rhs[2] + m[3][i] * rhs[3];
	
	}
	return newMatrixRow;
}
//checks if two matrixes are the same
inline bool mat4::operator==(const mat4& rhs)const {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m[i][j] != rhs[i][j]) {
				return false;
			}
		}
	}
	return true;
}
//checks if two matrixes are not the same
inline bool mat4::operator!=(const mat4& rhs)const {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m[i][j] != rhs[i][j]) {
				return !false;
			}
		}
	}
	return !true;
}
//returns the vector in the index position renge[0,3]
inline vec4& mat4::operator[](const unsigned int i) {
	return m[i];
}
//returns the vector in the index position renge[0,3]
inline const vec4& mat4::operator[](const unsigned int i)const  {
	return m[i];
}
//returns the determinant of a 2x2 matrix
inline float determinant2x2(float a, float b, float c, float d) {
	return a * d - b * c;
}
//returns the determinant of a 3x3 matrix
inline float determinant3x3(float a, float b, float c,
	float d, float e, float f,
	float h, float i, float j) {
	return (a * determinant2x2(e, f, i, j) - b * determinant2x2(d, f, h, j) + c * determinant2x2(d, e, h, i));
}
//returns the determinant of a 4x4 matrix
inline float determinant(const mat4& m) {
	return m[0][0] * (m[1][1] * determinant2x2(m[2][2], m[2][3], m[3][2], m[3][3]) - m[1][2] * determinant2x2(m[2][1], m[2][3], m[3][1], m[3][3]) + m[1][3] * determinant2x2(m[2][1], m[2][2], m[3][1], m[3][2])) -
		   m[0][1] * (m[1][0] * determinant2x2(m[2][2], m[2][3], m[3][2], m[3][3]) - m[1][2] * determinant2x2(m[2][0], m[2][3], m[3][0], m[3][2]) + m[1][3] * determinant2x2(m[2][0], m[2][2], m[3][0], m[3][2])) +
		   m[0][2] * (m[1][0] * determinant2x2(m[2][1], m[2][3], m[3][1], m[3][3]) - m[1][1] * determinant2x2(m[2][0], m[2][3], m[3][0], m[3][3]) + m[1][3] * determinant2x2(m[2][0], m[2][1], m[3][0], m[3][1])) -
	   	   m[0][3] * (m[1][0] * determinant2x2(m[2][1], m[2][2], m[3][1], m[3][2]) - m[1][1] * determinant2x2(m[2][0], m[2][2], m[3][0], m[3][2]) + m[1][2] * determinant2x2(m[2][0], m[2][1], m[3][0], m[3][1]));
}
inline mat4 transpose(const mat4& m);
//returns the inverse of a matrix sent in
inline mat4 inverse(const mat4& m) {
	mat4 inv;
	if (determinant(m) == 0) {
		return inv;
	}
	mat4 cofactorMatrix;
	//creating 16 coefficinet matrixes to use in adjugate formula
	cofactorMatrix[0][0] = determinant3x3(m[1][1], m[1][2], m[1][3],
										  m[2][1], m[2][2], m[2][3],  
										  m[3][1], m[3][2], m[3][3]);
	
	cofactorMatrix[0][1] = -determinant3x3(m[1][0], m[1][2], m[1][3],
										  m[2][0], m[2][2], m[2][3],
										  m[3][0], m[3][2], m[3][3]);

	cofactorMatrix[0][2] = determinant3x3(m[1][0], m[1][1], m[1][3],
										  m[2][0], m[2][2], m[2][3],
										  m[3][0], m[3][2], m[3][3]);

	cofactorMatrix[0][3] = -determinant3x3(m[1][0], m[1][1], m[1][2],
										  m[2][0], m[2][1], m[2][2],
										  m[3][0], m[3][1], m[3][2]);

	cofactorMatrix[1][0] = -determinant3x3(m[0][1], m[0][2], m[0][3],
										  m[2][1], m[2][2], m[2][3],
										  m[3][1], m[3][2], m[3][3]);

	cofactorMatrix[1][1] = determinant3x3(m[0][0], m[0][2], m[0][3],
										  m[2][0], m[2][2], m[2][3],
										  m[3][0], m[3][2], m[3][3]);

	cofactorMatrix[1][2] = -determinant3x3(m[0][0], m[0][1], m[0][3],
										  m[2][0], m[2][1], m[2][3],
										  m[3][0], m[3][1], m[3][3]);

	cofactorMatrix[1][3] = determinant3x3(m[0][0], m[0][1], m[0][2],
										  m[2][0], m[2][1], m[2][2],
										  m[3][0], m[3][1], m[3][2]);

	cofactorMatrix[2][0] = determinant3x3(m[0][1], m[0][2], m[0][3],
										  m[1][1], m[1][2], m[1][3],
										  m[3][1], m[3][2], m[3][3]);

	cofactorMatrix[2][1] = -determinant3x3(m[0][0], m[0][2], m[0][3],
										  m[1][0], m[1][2], m[1][3],
										  m[3][0], m[3][2], m[3][3]);

	cofactorMatrix[2][2] = determinant3x3(m[0][0], m[0][1], m[0][3],
										  m[1][0], m[1][1], m[1][3],
										  m[3][0], m[3][1], m[3][3]);

	cofactorMatrix[2][3] = -determinant3x3(m[0][0], m[0][1], m[0][2],
										  m[1][0], m[1][1], m[1][2],
										  m[3][0], m[3][1], m[3][2]);

	cofactorMatrix[3][0] = -determinant3x3(m[0][1], m[0][2], m[0][3],
										  m[1][1], m[1][2], m[1][3],
										  m[2][1], m[2][2], m[2][3]);

	cofactorMatrix[3][1] = determinant3x3(m[0][0], m[0][2], m[0][3],
										  m[1][0], m[1][2], m[1][3],
										  m[2][0], m[2][2], m[2][3]);

	cofactorMatrix[3][2] = -determinant3x3(m[0][0], m[0][1], m[0][3],
										  m[1][0], m[1][1], m[1][3],
										  m[2][0], m[2][1], m[2][3]);

	cofactorMatrix[3][3] = determinant3x3(m[0][0], m[0][1], m[0][2],
										  m[1][0], m[1][1], m[1][2],
										  m[2][0], m[2][1], m[2][2]);

	float a = m[1][3];
	float b = m[2][3];
	float c = m[3][3];

	float detA = determinant3x3(m[1][1], m[1][2],a,
								m[2][1], m[2][2], b, // finding dterminant
								m[3][1], m[3][2], c);



	inv = transpose(cofactorMatrix); //transposing matrix
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			inv[i][j] *= (1 / detA); //getting the final invers matrix
		}

	}


	return inv;
}
//returns the transpose of a matrix
inline mat4 transpose(const mat4& m) {
	mat4 transpose(vec4(m[0][0], m[1][0], m[2][0], m[3][0]),
				   vec4(m[0][1], m[1][1], m[2][1], m[3][1]), 
				   vec4(m[0][2], m[1][2], m[2][2], m[3][2]),
				   vec4(m[0][3], m[1][3], m[2][3], m[3][3]));
	
	return transpose;
}
//returns the x rotation matrix
inline mat4 rotationx(const float rad) {
	mat4 t(vec4(1, 0, 0, 0),
		   vec4(0, cos(rad), sin(rad), 0),
		   vec4(0, -sin(rad), cos(rad), 0), //rotaion matrix around x
		   vec4(0, 0, 0, 1)
	) ;
	return t;
}
//returns the y rotation matrix
inline mat4 rotationy(const float rad) {

	mat4 t(vec4(cos(rad), 0, -sin(rad), 0), //rotaion matrix around y
		   vec4(0, 1, 0, 0),
		   vec4(sin(rad), 0, cos(rad), 0),
		   vec4(0, 0, 0, 1)
	);
	return t;
}
//returns the z rotation matrix
inline mat4 rotationz(const float rad) {
	float f = -rad;
	mat4 t(vec4(cos(f), -sin(f), 0, 0),
		   vec4(sin(f), cos(f),0, 0), //rotaion matrix around z
		   vec4(0, 0, 1, 0),
		   vec4(0, 0, 0, 1));
	return t;
}
//returns the axis rotatin matrix of the radian and vector
inline mat4 rotationaxis(const vec3& v, const float rad) {

	mat4 uxu(vec4(v[0] * v[0], v[0] * v[1], v[0] * v[2], 0),
			 vec4(v[0] * v[1], v[1] * v[1], v[1] * v[2], 0), //outer product matrix
			 vec4(v[0] * v[2], v[2] * v[1], v[2] * v[2], 0),
			 vec4(0,0,0,1));
	mat4 ux(vec4(0,-v[2],v[1],0), vec4(v[2],0,-v[0],0), vec4(-v[1],v[0],0,0), vec4(0,0,0,1)); //cross product matrix
	mat4 I;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			I[i][j] *= cos(rad);  //does (cos(rad))*I
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ux[i][j] *= sin(rad); //does (sin(rad))*ux
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			uxu[i][j] *= (1-cos(rad));//does (1 - cos(rad))*uxu
		}
	}
	mat4 R;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			R[i][j] = I[i][j] + ux[i][j] + uxu[i][j]; //adds all thenumbers from the matrixes togheter in a matrix
		}
	}
	return transpose(R); //transposes matrix
}

inline mat4 lookat(const vec3& eye, const vec3& at, const vec3& up) {
	vec3 v = normalize(eye - at);
	vec3 r = normalize(cross(v, -up));
	vec3 u = cross(v, r);
	mat4 m(vec4(r.x, r.y, r.z, dot(-eye, r)), vec4(u.x, u.y, u.z, dot(-eye, u)), vec4(v.x, v.y, v.z, dot(-eye, v)), vec4(0, 0, 0, 1));
	return transpose(m);
}

inline mat4 perspective(const float fovy, const float aspect, const float near, const float far) {
	float c = 1 / tanf(fovy / 2);
	mat4 p(vec4(c/aspect,0,0,0), vec4(0,c,0,0), vec4(0,0,-((far+near)/ (far - near)),-((2*far*near)/(far-near))), vec4(0,0,-1,0));
	return transpose(p);
}



