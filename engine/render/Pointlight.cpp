#include "config.h"
#include "PointLight.h"

PointLight::PointLight()
{
	position = vec3(0, 2.0, -2);
	color = vec3(1.0, 1.0, 1.0);
	intesity = 1;
	angle = 0;
}

PointLight::PointLight(vec3 pos, vec3 color, float intesity)
{
	this->color = color;
	this->position = pos;
	this->intesity = intesity;
	angle = 0;
}

PointLight::~PointLight()
{
}

void PointLight::draw(GLint v, vec3 data) {
	glUniform3fv(v, 1, (GLfloat*)&data);

}

void PointLight::moveLightInCircle(int time) {
	float radius = 0.2;
	angle += 0.05;
	float sinus = sin(angle) * radius;
	float cosinus = cos(angle) * radius;
	position.x = position.x + cosinus;
	position.z = position.z + sinus;

}