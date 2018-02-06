#include "Camera.h"
#include "Registry.h"

// Constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(Properties::Get<float>("cameraSpeed")), MouseSensitivity(Properties::Get<float>("cameraSensitivity")), Zoom(Properties::Get<float>("cameraZoom"))
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
	projection = glm::perspective(glm::radians(fov), (float)Registry::GetRenderEngine()->GetWidth() / (float)Registry::GetRenderEngine()->GetHeight(), 0.01f, 100000000.0f);
}
// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(Properties::Get<float>("cameraSpeed")), MouseSensitivity(Properties::Get<float>("cameraSensitivity")), Zoom(Properties::Get<float>("cameraZoom"))
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
	projection = glm::perspective(glm::radians(fov), (float)Registry::GetRenderEngine()->GetWidth() / (float)Registry::GetRenderEngine()->GetHeight(), 0.1f, 1000000000.0f);
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
// FIXME TODO if the look at feature is enable return the matrix that looks at the object
glm::mat4 Camera::GetViewMatrix()
{
	return mustLookAt ? glm::lookAt(Position, lookAtTarget->GetPostion(), Up) : glm::lookAt(Position, Position + Front, Up);
}

// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == UP)
		Position += Up * velocity;
	if (direction == DOWN)
		Position -= Up * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

// Calculates the front vector from the Camera's (updated) Eular Angles
// FIXME TODO calculate the look at target vector
void Camera::updateCameraVectors()
{
	if (mustLookAt == false) {
		mustLookAt = false;
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
	else {

	}
}

// Move the camera in a specific direction
// FIXME TODO modify to look at a target point, the lookAtTarget's position
void Camera::Move(Camera_Movement direction, float delta) {
	float velocity = MovementSpeed * delta;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}

// Sets the Cameras look at target, must use function EnableLookAt() to use
void Camera::SetCameraLookAtTarget(Object* target) {
	lookAtTarget = target;
};

// Look At target enablers and diablers. Tells the camera wether or not to look at a target or not
void Camera::EnableLookAt() {
	if (&lookAtTarget != nullptr) {
		mustLookAt = true;
	}
};

// Diables the look at function
void Camera::DisableLookAt() {
	mustLookAt = false;
};

glm::mat4 Camera::GetProjectionMatrix() {
	return projection;
};