#pragma once

// Taken from here: https://github.com/TheCherno/RayTracing

#include <glm/glm.hpp>
#include <vector>
#include <QObject>
#include <QQuickItem>
#include <QString>

class Camera : public QObject
{
	Q_OBJECT
	QML_ELEMENT
	Q_ENUMS(Direction)
public:
	enum class Direction
	{
		None,
		Forward,
		Backward,
		Left,
		Right
	};

	Camera(float verticalFOV, float nearClip, float farClip);

	bool OnUpdate(float ts);
	void OnResize(uint32_t width, uint32_t height);

	const glm::mat4 &GetProjection() const { return m_Projection; }
	const glm::mat4 &GetInverseProjection() const { return m_InverseProjection; }
	const glm::mat4 &GetView() const { return m_View; }
	const glm::mat4 &GetInverseView() const { return m_InverseView; }

	const glm::vec3 &GetPosition() const { return m_Position; }
	const glm::vec3 &GetDirection() const { return m_ForwardDirection; }

	const std::vector<glm::vec3> &GetRayDirections() const { return m_RayDirections; }

	float GetRotationSpeed();

public Q_SLOTS:
	void setLookXDirection(Direction direction);
	void setLookYDirection(Direction direction);
	void setWalkXDirection(Direction direction);
	void setWalkYDirection(Direction direction);

private:
	void RecalculateProjection();
	void RecalculateView();
	void RecalculateRayDirections();

private:
	glm::mat4 m_Projection{1.0f};
	glm::mat4 m_View{1.0f};
	glm::mat4 m_InverseProjection{1.0f};
	glm::mat4 m_InverseView{1.0f};

	float m_VerticalFOV = 45.0f;
	float m_NearClip = 0.1f;
	float m_FarClip = 100.0f;

	glm::vec3 m_Position{0.0f, 0.0f, 0.0f};
	glm::vec3 m_ForwardDirection{0.0f, 0.0f, 0.0f};

	// Cached ray directions
	std::vector<glm::vec3> m_RayDirections;

	glm::vec2 m_LastMousePosition{0.0f, 0.0f};

	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

private:
	Direction m_lookXDirection = Direction::None;
	Direction m_lookYDirection = Direction::None;
	Direction m_walkXDirection = Direction::None;
	Direction m_walkYDirection = Direction::None;
};