#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Mesh.h"
#include "memory"

class Model
{
private:
	
	std::shared_ptr<Mesh> m_Mesh;
	std::shared_ptr<Texture> m_Texture;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;


public:

	Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 position, glm::vec3 rotation);
	Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 position);
	Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex);
	~Model();

	std::shared_ptr<Mesh> GetMesh() const { return m_Mesh; };
	void Bind() const;
	void UnBind() const;

	virtual void Draw(Shader& shader) const;

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void SetScale(glm::vec3);

	void SetPosition(glm::vec3 nPos) { m_Position = nPos; };
	glm::vec3 GetPosition() const { return m_Position; };
};

