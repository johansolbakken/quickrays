#include "camera.h"

// Taken from here: https://github.com/TheCherno/RayTracing

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

Camera::Camera(float verticalFOV, float nearClip, float farClip)
	: m_VerticalFOV(verticalFOV), m_NearClip(nearClip), m_FarClip(farClip)
{
	m_ForwardDirection = glm::vec3(0, 0, -1);
	m_Position = glm::vec3(0, 0, 6);
}

bool Camera::OnUpdate(float ts = 1.0f)
{

    /*
	glm::vec2 mousePos = Input::GetMousePosition();
	glm::vec2 delta = (mousePos - m_LastMousePosition) * 0.002f;
	m_LastMousePosition = mousePos;
*/
/*
	if (!Input::IsMouseButtonDown(MouseButton::Right))
	{
		Input::SetCursorMode(CursorMode::Normal);
		return false;
	}

	Input::SetCursorMode(CursorMode::Locked);
*/
	bool moved = false;

	constexpr glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
	glm::vec3 rightDirection = glm::cross(m_ForwardDirection, upDirection);

	float speed = 0.5f;

	// Movement
	if (m_walkYDirection == Direction::Forward)
	{
		m_Position += m_ForwardDirection * speed * ts;
		moved = true;
	}
	else if (m_walkYDirection == Direction::Backward)
	{
		m_Position -= m_ForwardDirection * speed * ts;
		moved = true;
	}
	if (m_walkXDirection == Direction::Left)
	{
		m_Position -= rightDirection * speed * ts;
		moved = true;
	}
	else if (m_walkXDirection == Direction::Right)
	{
		m_Position += rightDirection * speed * ts;
		moved = true;
	}
    /*
	if (Input::IsKeyDown(KeyCode::Q))
	{
		m_Position -= upDirection * speed * ts;
		moved = true;
	}
	else if (Input::IsKeyDown(KeyCode::E))
	{
		m_Position += upDirection * speed * ts;
		moved = true;
	}*/

	// Rotation
    /*
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = delta.y * GetRotationSpeed();
		float yawDelta = delta.x * GetRotationSpeed();

		glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
			glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
		m_ForwardDirection = glm::rotate(q, m_ForwardDirection);

		moved = true;
	} old code*/

    if (m_lookYDirection == Direction::Backward)
    {
        float pitchDelta = 1.0f * GetRotationSpeed();
        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
            glm::angleAxis(0.0f, glm::vec3(0.f, 1.0f, 0.0f))));
        m_ForwardDirection = glm::rotate(q, m_ForwardDirection);
        moved = true;
    } else if (m_lookYDirection == Direction::Forward) {
        float pitchDelta = -1.0f * GetRotationSpeed();
        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
            glm::angleAxis(0.0f, glm::vec3(0.f, 1.0f, 0.0f))));
        m_ForwardDirection = glm::rotate(q, m_ForwardDirection);
        moved = true;
    } 
    if (m_lookXDirection == Direction::Left)
    {
        float yawDelta = -1.0f * GetRotationSpeed();
        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(0.0f, rightDirection),
            glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
        m_ForwardDirection = glm::rotate(q, m_ForwardDirection);
        moved = true;
    } else if (m_lookXDirection == Direction::Right) {
        float yawDelta = 1.0f * GetRotationSpeed();
        glm::quat q = glm::normalize(glm::cross(glm::angleAxis(0.0f, rightDirection),
            glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
        m_ForwardDirection = glm::rotate(q, m_ForwardDirection);
        moved = true;
    }


	if (moved)
	{
		RecalculateView();
		RecalculateRayDirections();
	}
    
	return moved;
}

void Camera::handleActionTriggered(const QString &action)
{
    if (action == "MoveForward") {
        m_walkYDirection = Direction::Forward;
    } else if (action == "MoveBackward") {
        m_walkYDirection = Direction::Backward;
    } else if (action == "MoveLeft") {
        m_walkXDirection = Direction::Left;
    } else if (action == "MoveRight") {
        m_walkXDirection = Direction::Right;
    } else if (action == "MoveStopX") {
        m_walkXDirection = Direction::None;
    } else if (action == "MoveStopY") {
        m_walkYDirection = Direction::None;
    }

    if (action == "LookUp") {
        m_lookYDirection = Direction::Forward;
    } else if (action == "LookStopY") {
        m_lookYDirection = Direction::None;
    } else if (action == "LookDown") {
        m_lookYDirection = Direction::Backward;
    } else if (action == "LookLeft") {
        m_lookXDirection = Direction::Left;
    } else if (action == "LookRight") {
        m_lookXDirection = Direction::Right;
    } else if (action == "LookStopX") {
        m_lookXDirection = Direction::None;
    }
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (width == m_ViewportWidth && height == m_ViewportHeight)
		return;

	m_ViewportWidth = width;
	m_ViewportHeight = height;

	RecalculateProjection();
	RecalculateRayDirections();
}

float Camera::GetRotationSpeed()
{
	return 0.03f;
}

void Camera::RecalculateProjection()
{
	m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
	m_InverseProjection = glm::inverse(m_Projection);
}

void Camera::RecalculateView()
{
	m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));
	m_InverseView = glm::inverse(m_View);
}

void Camera::RecalculateRayDirections()
{
	m_RayDirections.resize(m_ViewportWidth * m_ViewportHeight);

	for (uint32_t y = 0; y < m_ViewportHeight; y++)
	{
		for (uint32_t x = 0; x < m_ViewportWidth; x++)
		{
			glm::vec2 coord = { (float)x / (float)m_ViewportWidth, (float)y / (float)m_ViewportHeight };
			coord = coord * 2.0f - 1.0f; // -1 -> 1

			glm::vec4 target = m_InverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
			glm::vec3 rayDirection = glm::vec3(m_InverseView * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
			m_RayDirections[x + y * m_ViewportWidth] = rayDirection;
		}
	}
}