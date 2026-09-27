#pragma once
#include <GL/glew.h>
#include "core/mat4.h"
class PointLight
{
public:
	PointLight();
	PointLight(vec3 pos, vec3 color, float intesity);
	~PointLight();
	void draw(GLint v, vec3 data);
	void moveLightInCircle(int time);
	vec3 position;
	vec3 color;
	float intesity = 0;
	float angle = 0;
private:

};

//inline PointLight::PointLight()
//{
//	position = vec3(0, 2.0, -2);
//	color = vec3(1.0, 1.0, 1.0);
//	intesity = 1;
//	angle = 0;
//}
//
//inline PointLight::PointLight(vec3 pos, vec3 color, float intesity)
//{
//	this->color = color;
//	this->position = pos;
//	this->intesity = intesity;
//	angle = 0;
//}
//
//inline PointLight::~PointLight()
//{
//}
//
//inline void PointLight::draw(GLint v, vec3 data) {
//	glUniform3fv(v,1,(GLfloat*)&data);
//
//}
//
//inline void PointLight::moveLightInCircle(int time) {
//	float radius = 0.2;
//	angle += 0.05;
//	float sinus = sin(angle) * radius;
//	float cosinus = cos(angle) * radius;
//	position.x = position.x + cosinus;
//	position.z = position.z + sinus;
//	
//}
