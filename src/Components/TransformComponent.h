#pragma once
#include "GameComponent.h"
#include <glm/glm.hpp>
#include "src/Vector2.h"
/**
Transform component, which is used for the position, scale and rotation of a game object.
*/
class TransformComponent : public GameComponent {
public:
	/**
	Move the transform in 3D space by a specified vector.
	*/
	void move(glm::vec3 moveVector/**How much the transform is to be moved in 3D space.*/);
	/**
	Move the transform in 2D space by a specified vector.
	*/
	void move2D(Vector2 moveVector/**How much the transform is to be moved in 2D space.*/);
	/**
	Rotate the transform in 3D space.
	*/
	void rotate(glm::vec3 rotation/**Rotation per axis in radians.*/);
	/**
	Scale the transform in 3D space.
	*/
	void scale(glm::vec3 scale/**Scale in relation to actual size in every axis.*/);
	/**
	Get the position of the transform.
	*/
	glm::vec3 getPosition();
	/**
	Get the scale of each axis of the transform.
	*/
	glm::vec3 getScale();
	/**
	Get rotation around the z axis of the transform.
	*/
	float getRotationAroundZAxis();
	/**
	Get the global transform matrix.
	*/
	glm::mat4 getGlobalTransform();
	/**
	Set position of transform in 3D space.
	*/
	void setPosition(glm::vec3 newPosition/**The transform's new position.*/);

protected:
	TransformComponent(GameObject *gameObject);
private:
	glm::mat4 getLocalTransform();
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	friend class GameObject;
};
