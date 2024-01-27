#include "../Public/MovingCar.h"
#include "../Public/Math.h"
#include <iostream>

Car::Car(std::shared_ptr<Mesh> CarMesh, std::shared_ptr<Texture> Tex, glm::vec3 Position,
	glm::vec2 Center, float amplitude, std::shared_ptr<Mesh> LightBulbMesh)
	: Model(CarMesh, Tex, Position), m_XZCenter(Center), m_Amplitude(amplitude)
{
	m_StaringCamera.reset(new Camera(glm::vec3(0.f, 5.f, 20.f)));
	m_ThirdPersonCamera.reset(new Camera(glm::vec3(Position) + glm::vec3(0.f, 0.2f, 0.f)));
	//m_StaringCamera->BlockInput = m_ThirdPersonCamera->BlockInput = true;

	m_StaringCamera->SetOrientation(GetPosition() - m_StaringCamera->GetPosition());
	m_ThirdPersonCamera->SetOrientation(-GetPosition());

	if (LightBulbMesh != nullptr)
	{
		m_Lightbulb.reset (new Model(LightBulbMesh, nullptr));
		m_Lightbulb->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	}
}

Car::~Car()
{
	Model::~Model();
}

void Car::Tick(double delta)
{
	SetPosition(glm::vec3(m_Amplitude * std::sin(glm::radians(m_CurrentAngle)), GetPosition().y, m_Amplitude * std::cos(glm::radians(m_CurrentAngle))));
	m_CurrentAngle = CalcAngleDegrees(m_CurrentAngle + delta * m_Degrees);
	RotateY(glm::radians(m_CurrentAngle) + glm::radians(90.f));
	
	if (m_Lightbulb)
	{
		m_Lightbulb->SetPosition(GetPosition() +
			glm::vec3(0.5f * std::sin(glm::radians(m_CurrentAngle)), 0.8f, 0.0f));
	}

	m_StaringCamera->SetOrientation(GetPosition() - m_StaringCamera->GetPosition());

	m_ThirdPersonCamera->SetPosition(GetPosition());
	m_ThirdPersonCamera->SetOrientation(-GetPosition());
}

void Car::Draw(Shader& shader) const
{
	shader.Bind();
	shader.SetUniform4f("u_Color", 1.f, 1.f, 1.f, 1.f);
	Model::Draw(shader);
}
