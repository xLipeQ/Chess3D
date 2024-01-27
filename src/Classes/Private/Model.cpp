#include "../Public/Model.h"
#include <glm/gtc/type_ptr.hpp>
#include "../Public/Math.h"



Model::Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
	m_Mesh(Mesh), m_Texture(Tex), m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
}

Model::Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 position, glm::vec3 rotation) :
	m_Mesh(Mesh), m_Texture(Tex), m_Position(position), m_Rotation(rotation)
{
	m_Scale = glm::vec3(1.f);
}

Model::Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex, glm::vec3 position) :
	m_Mesh(Mesh), m_Texture(Tex), m_Position(position)
{
	m_Scale = glm::vec3(1.f);
	m_Rotation = glm::vec3(0.f);
}

Model::Model(std::shared_ptr<Mesh> Mesh, std::shared_ptr<Texture> Tex) :
	m_Mesh(Mesh), m_Texture(Tex)
{
	m_Scale = glm::vec3(1.f);
	m_Rotation = glm::vec3(0.f);
	m_Position = glm::vec3(0.f);
}

Model::~Model()
{
}

void Model::Bind() const 
{
	m_Mesh->Bind();
	if (m_Texture != nullptr)
		m_Texture->Bind(); 
}
void Model::UnBind() const 
{
	m_Mesh->UnBind();
	if (m_Texture != nullptr)
		m_Texture->UnBind();
}

void Model::Draw(Shader& shader) const
{
	Bind();
	shader.Bind();

	glm::mat4 ScaleMatrix = ScaleObject(m_Scale);

	glm::mat4 RotationMatrix = RotateObject(m_Rotation);

	glm::mat4 Translation = TransateObject(m_Position);

	shader.SetUniformMatrix4fv("u_Model", glm::value_ptr(Translation * RotationMatrix * ScaleMatrix));
	
	if(m_Texture != nullptr)
		shader.SetUniform1i("u_Texture", 0);

	GLCall(glDrawElements(GL_TRIANGLES, m_Mesh->GetIndexCount(), GL_UNSIGNED_INT, 0));

	UnBind();
	shader.UnBind();
}

void Model::RotateX(float angle)
{
	m_Rotation.x = angle;
}

void Model::RotateY(float angle)
{
	m_Rotation.y = angle;
}
void Model::RotateZ(float angle)
{
	m_Rotation.z = angle;
}

void Model::SetScale(glm::vec3 scale)
{
	m_Scale = scale;
}