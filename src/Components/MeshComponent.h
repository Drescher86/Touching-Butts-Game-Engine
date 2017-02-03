#pragma once
#include "GameComponent.h"
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include <SRE/Texture.hpp>
#include <memory>
/**
Mesh component. Used for 3D.
*/
class MeshComponent : public GameComponent {
public:
	/**
	Set mesh.
	*/
	void setMesh(std::shared_ptr<SRE::Mesh> mesh/**Shared pointer to mesh that is to be set.*/);
	/**
	Set shader.
	*/
	void setShader(std::shared_ptr<SRE::Shader> shader/**Shared pointer to mesh that is to be set.*/);
	/**
	Set texture. If not set, must set color.
	*/
	void setTexture(std::shared_ptr<SRE::Texture> texture/**Shared pointer to texture that is to be set.*/);
	/**
	Set color. If not set, must set texture.
	*/
	void setColor(glm::vec4 color/**Vector4 representing the color of the mesh.*/);
protected:
	void render() override;
	MeshComponent(GameObject* gameObject);
private:
	std::shared_ptr<SRE::Mesh> m_mesh;
	std::shared_ptr<SRE::Shader> m_shader;
	std::shared_ptr<SRE::Texture> m_texture;
	glm::vec4 m_color;
	friend class GameObject;
};
