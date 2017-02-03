#pragma once
#include <glm\glm.hpp>
#include "Interpolation.hpp"
/*!
Particle Animation Enum.
*/
enum class ParticleAnimation {
	FIXED_STATIC,
	RANDOM_STATIC,
	LINEAR_DYNAMIC,
	SPLINE_DYNAMIC
};
/*!
Particle Animation Behavior Enum.
*/
enum class AnimationBehavior {
	STOP_AT_END,
	GO_BACK,
	START_OVER
};
/**
Particle class.
*/
class Particle {
public:
	/**
	Creates new particle.
	*/
	Particle(glm::vec3 position/**Start position.*/, glm::vec3 velocity/**Velocity.*/, float timeOfBirth/**Time of birth.*/);
	/**
	Creates a new particle.
	*/
	Particle(glm::vec3 position/**Start position.*/, glm::vec3 velocity/**Velocity.*/, float timeOfBirth/**Time of birth.*/, glm::vec4 color/**Color.*/, float size/**Size.*/);
	/**
	Animate particle color through its life time, using a specific interpolation type. 
	FIXED_STATIC only color1 is used.
	RANDOM_STATIC uses none of the colors.
	LINEAR_DYNAMIC only color1 and color2 are used.
	SPLINE_DYNAMIC all colors are used.
	*/
	void animateParticleColor(ParticleAnimation type/**ParticleAnimation type.*/, glm::vec4 color1 = glm::vec4()/**Animation start color. Defaults to black.*/, glm::vec4 color2 = glm::vec4()/**Animation second color. Defaults to black.*/, glm::vec4 color3 = glm::vec4()/**Animation third color. Defaults to black.*/, glm::vec4 color4 = glm::vec4()/**Animation fourth color. Defaults to black.*/);
	/**
	Animate particle size through its life time, using a specific interpolation type.
	FIXED_STATIC only size1 is used.
	RANDOM_STATIC uses none of the sizes.
	LINEAR_DYNAMIC only size1 and size2 are used.
	SPLINE_DYNAMIC all sizes are used.
	*/
	void animateParticleSize(ParticleAnimation type/**ParticleAnimation type.*/, float size1 = 0.0f/**Animation start size. Defaults to 0.*/, float size2 = 0.0f/**Animation second size. Defaults to 0.*/, float size3 = 0.0f/**Animation third size. Defaults to 0.*/, float size4 = 0.0f/**Animation fourth size. Defaults to 0.*/);
	/**
	Update particle.
	*/
	void update(float deltaTime/**Update timer in seconds.*/);
	/**
	Set animation time.
	*/
	void setAnimationTime(float time/**Animation time in seconds.*/);
	/**
	Set animation time for color.
	*/
	void setAnimationTimeColor(float time/**Animation time in seconds.*/);
	/**
	Set animation time for size.
	*/
	void setAnimationTimeSize(float time/**Animation time in seconds.*/);
	/**
	Set animation behavior.
	*/
	void setAnimationBehavior(AnimationBehavior behavior/**BehaviorType.*/);
	/**
	Set animation behavior for color.
	*/
	void setAnimationBehaviorColor(AnimationBehavior behavior/**BehaviorType.*/);
	/**
	Set animation behavior for size.
	*/
	void setAnimationBehaviorSize(AnimationBehavior behavior/**BehaviorType.*/);

	/**
	Particle position.
	*/
	glm::vec3 position;
	/**
	Particle velocity.
	*/
	glm::vec3 velocity;
	/**
	Particle time of birth.
	*/
	float timeOfBirth;
	/**
	Particle color expressed as a vector4.
	*/
	glm::vec4 color;
	/**
	Particle size.
	*/
	float size;


private:
	glm::vec4 randomStatic(int min, int max, int divisor);
	void updateColor(float deltaTime);
	void updateSize(float deltaTime);
	//glm::vec4 linearInterpolation(glm::vec4 point1, glm::vec4 point2);

	ParticleAnimation m_colorAnimationType;
	ParticleAnimation m_sizeAnimationType;

	std::vector<glm::vec4> m_pointsColor;
	std::vector<glm::vec4> m_pointsSize;
	
	float m_animationTimeColor;
	float m_animationTimeSize;
	float m_currentTimeInAnimationColor;
	float m_currentTimeInAnimationSize;

	AnimationBehavior m_animBehaviorColor;
	AnimationBehavior m_animBehaviorSize;

	bool m_goingBackColor = false;
	bool m_goingBackSize = false;

};