#include "MeshComponent.h"
#include "src/GameObject.h"
#include "TransformComponent.h"
#include <SRE/SimpleRenderEngine.hpp>

void MeshComponent::render()
{
	if (m_mesh != nullptr && m_shader != nullptr) {
		auto transform = gameObject->getComponent<TransformComponent>();
		if (transform != nullptr) {
			if (m_texture != nullptr) {
				m_shader->setTexture("texture", m_texture.get());
			}
			else {
				m_shader->setVector("color", m_color);
			}
			SRE::SimpleRenderEngine::instance->draw(m_mesh.get(), transform->getGlobalTransform(), m_shader.get());
		}
	}
}

void MeshComponent::setMesh(std::shared_ptr<SRE::Mesh> mesh)
{
	m_mesh = mesh;
}

void MeshComponent::setShader(std::shared_ptr<SRE::Shader> shader)
{
	m_shader = shader;
}

void MeshComponent::setTexture(std::shared_ptr<SRE::Texture> texture)
{
	m_texture = texture;
}

void MeshComponent::setColor(glm::vec4 color)
{
	m_color = color;
}

MeshComponent::MeshComponent(GameObject * gameObject)
	:GameComponent(gameObject) {
}
