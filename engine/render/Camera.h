#pragma once
#include "core/mat4.h"
#include "math.h"
class Camera
{
public:
	Camera();
	~Camera();
	void createCamera(vec3 pos, vec3 front, vec3 up);
	Camera& operator=(const Camera&);
	mat4 getViewMatrix();
	void updateCameraVectors();
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	vec3 position;
	vec3 cameraFront;
	vec3 cameraUp;
	vec3 cameraRight;
	vec3 WorldUp = vec3(0.0f, 1.0f, 0.0f);
	float cameraYaw = -90.0f;
	float cameraPitch = 0.0f;
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	float MouseSensitivity = 0.1;
	float Zoom = 45;
private:

};

inline Camera::Camera()
{
}

inline Camera::~Camera()
{
}

inline mat4 Camera::getViewMatrix(){
	return lookat(position, position + cameraFront, cameraUp);
}

inline void Camera::createCamera(vec3 pos, vec3 front, vec3 up) {
	position = pos;
	cameraFront = front;
	cameraUp = up;
}
inline void Camera::updateCameraVectors()
{
	double pi = 3.14159265359;
	// calculate the new Front vector
	vec3 front;
	front.x = cos( cameraYaw * (pi/180)) * cos(cameraPitch * (pi / 180));
	front.y = sin(cameraPitch * (pi / 180));
	front.z = sin(cameraYaw * (pi / 180)) * cos(cameraPitch * (pi / 180));
	cameraFront = normalize(front);
	// also re-calculate the Right and Up vector
	cameraRight = normalize(cross(cameraFront, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = normalize(cross(cameraRight, cameraFront));
}
inline void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{


	cameraYaw += xoffset* MouseSensitivity;
	cameraPitch += yoffset * MouseSensitivity;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (cameraPitch > 89.0f)
			cameraPitch = 89.0f;
		if (cameraPitch < -89.0f)
			cameraPitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}
inline void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}

inline Camera& Camera::operator=(const Camera& cam) {
	Camera c;
	c.cameraFront = cameraFront;
	c.cameraPitch = cameraPitch;
	c.cameraRight = cameraRight;
	c.cameraUp = cameraUp;
	c.cameraYaw = cameraYaw;
	c.position = position;
	
	return c;
}
