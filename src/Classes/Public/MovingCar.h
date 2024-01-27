#pragma once
#include "Model.h"
#include "Camera.h"

class Car : public Model
{
private:

	std::shared_ptr<Camera> m_ThirdPersonCamera;
	std::shared_ptr<Camera> m_StaringCamera;
	glm::vec2 m_XZCenter;
	float m_Amplitude;
	float m_Degrees = 90.f;
	float m_CurrentAngle = 0.f;

	std::shared_ptr<Model> m_Lightbulb = nullptr;

public:
	Car(std::shared_ptr<Mesh> CarMesh, std::shared_ptr<Texture> Tex, glm::vec3 Position, 
		glm::vec2 Center, float amplitude, std::shared_ptr<Mesh> LightBulbMesh);
	~Car();

	std::shared_ptr<Camera> GetAThirdCamera() const { return m_ThirdPersonCamera; };
	std::shared_ptr<Camera> GetStaringCamera() const { return m_StaringCamera; };

	std::shared_ptr<Model> GetLightBulb() const { return m_Lightbulb; };

	void Tick(double delta);
	void Draw(Shader& shader) const;

};


