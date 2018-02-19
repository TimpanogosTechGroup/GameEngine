#pragma once
#ifndef CAMERA_H
#define CAMERA_H

//#include <glad/glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>
#include "Model.h"
#include "Properties.h"

using namespace glm;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = Properties::Get<float>("cameraYaw"), float pitch = Properties::Get<float>("cameraPitch"));

	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

	// Move the camera in a specific direction
	void Move(Camera_Movement dir, float delta);

	// Sets the Cameras look at target, must use function EnableLookAt() to use
	void SetCameraLookAtTarget(Model* target);

	// Gets the perpective matrix of the camera
	glm::mat4 GetProjectionMatrix();

	// Look At target enablers and diablers. Tells the camera wether or not to look at a target or not
	void EnableLookAt();
	void DisableLookAt();

	// Getters and Setters
	vec3 GetPosition() { return Position; };
	vec3 GetFront() { return Front; };
	vec3 GetUp() { return Up; };
	vec3 GetRight() { return Right; };
	vec3 GetWorldUp() { return WorldUp; };

	float GetYaw() { return Yaw; };
	float GetPitch() { return Pitch; };
	float GetMovementSpeed() { return MovementSpeed; };
	float GetMouseSensitivity() { return MouseSensitivity; };
	float GetZoom() { return Zoom; };

	void SetPosition(vec3 position) { Position = position; };
	//void SetFront(vec3 front) { Front = front; };
	//void SetUp(vec3 up) { Up = up; };
	//void SetRight(vec3 right) { Right = right; };
	//void SetWorldUp(vec3 worldUp) { WorldUp = worldUp; };

	void SetYaw(float yaw) { Yaw = yaw; };
	void SetPitch(float pitch) {Pitch = pitch; };
	void SetMovementSpeed(float movementSpeed) { MovementSpeed = movementSpeed; };
	void SetMouseSensitivity(float mouseSensitivity) { MouseSensitivity = mouseSensitivity; };
	void SetZoom(float zoom) { Zoom = zoom; };

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();

	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	float fov = Properties::Get<float>("cameraFOV");

	// LookAtTarget
	bool mustLookAt = false;
	Model* lookAtTarget = nullptr;

	// Prespective matrix
	glm::mat4 projection;
};
#endif