#include "Particle.h"

Particle::Particle(glm::vec3 position, glm::vec3 velocity, float timeOfBirth)
	:position(position), velocity(velocity), timeOfBirth(timeOfBirth), m_animBehaviorColor(AnimationBehavior::STOP_AT_END), m_animBehaviorSize(AnimationBehavior::STOP_AT_END)
{
}

Particle::Particle(glm::vec3 position, glm::vec3 velocity, float timeOfBirth, glm::vec4 color, float size)
	: position(position), velocity(velocity), timeOfBirth(timeOfBirth), color(color), size(size), m_animBehaviorColor(AnimationBehavior::STOP_AT_END), m_animBehaviorSize(AnimationBehavior::STOP_AT_END)
{
}

void Particle::animateParticleColor(ParticleAnimation type, glm::vec4 color1, glm::vec4 color2, glm::vec4 color3, glm::vec4 color4)
{
	m_colorAnimationType = type;
	switch (type) {
		case ParticleAnimation::FIXED_STATIC:
			color = color1;
			break;
		case ParticleAnimation::RANDOM_STATIC:
			color = randomStatic(0, 100, 100);
			break;
		case ParticleAnimation::LINEAR_DYNAMIC:
			m_pointsColor.push_back(color1);
			m_pointsColor.push_back(color2);
			break;
		case ParticleAnimation::SPLINE_DYNAMIC:
			m_pointsColor.push_back(color1);
			m_pointsColor.push_back(color2);
			m_pointsColor.push_back(color3);
			m_pointsColor.push_back(color4);
			break;
	}
}
void Particle::animateParticleSize(ParticleAnimation type, float size1, float size2, float size3, float size4)
{
	m_sizeAnimationType = type;
	switch (type) {
	case ParticleAnimation::FIXED_STATIC:
		size = size1;
		break;
	case ParticleAnimation::RANDOM_STATIC:
		size = randomStatic(size1*100, size2*100, 100).x;
		break;
	case ParticleAnimation::LINEAR_DYNAMIC:
		m_pointsSize.push_back(glm::vec4(size1));
		m_pointsSize.push_back(glm::vec4(size2));
		break;
	case ParticleAnimation::SPLINE_DYNAMIC:
		m_pointsSize.push_back(glm::vec4(size1));
		m_pointsSize.push_back(glm::vec4(size2));
		m_pointsSize.push_back(glm::vec4(size3));
		m_pointsSize.push_back(glm::vec4(size4));
		break;
		break;
		break;
	}
}

void Particle::update(float deltaTime)
{
	updateColor(deltaTime);
	updateSize(deltaTime);
	

}

void Particle::updateSize(float deltaTime) {
	if (!m_goingBackSize) {
		m_currentTimeInAnimationSize += deltaTime;
	}
	else {
		m_currentTimeInAnimationSize -= deltaTime;
	}

	float t = m_currentTimeInAnimationSize / m_animationTimeColor;

	if (t > 1) {
		switch (m_animBehaviorSize) {
		case AnimationBehavior::STOP_AT_END:
			t = 1;
			break;
		case AnimationBehavior::START_OVER:
			m_currentTimeInAnimationSize = 0;
			t = 0;
			break;
		case AnimationBehavior::GO_BACK:
			m_goingBackSize = true;
		}
	}
	else if (t < 0) {
		m_goingBackSize = false;
		t = 0;
	}
	if (m_sizeAnimationType == ParticleAnimation::LINEAR_DYNAMIC) {
		Interpolation ip(&m_pointsSize);
		ip.setInterpolation(InterpolationType::Linear);
		size = ip.interpolate(t).x;
	}
	if (m_sizeAnimationType == ParticleAnimation::SPLINE_DYNAMIC) {
		Interpolation ip(&m_pointsSize);
		ip.setInterpolation(InterpolationType::Hermite);
		size = ip.interpolate(t).x;
	}
}

void Particle::updateColor(float deltaTime) {

	if (!m_goingBackColor) {
		m_currentTimeInAnimationColor += deltaTime;
	}
	else {
		m_currentTimeInAnimationColor -= deltaTime;
	}

	float t = m_currentTimeInAnimationColor / m_animationTimeColor;

	if (t > 1) {
		switch (m_animBehaviorColor) {
		case AnimationBehavior::STOP_AT_END:
			t = 1;
			break;
		case AnimationBehavior::START_OVER:
			m_currentTimeInAnimationColor = 0;
			t = 0;
			break;
		case AnimationBehavior::GO_BACK:
			m_goingBackColor = true;
		}
	}
	else if (t < 0) {
		m_goingBackColor = false;
		t = 0;
	}

	if (m_colorAnimationType == ParticleAnimation::LINEAR_DYNAMIC) {
		Interpolation ip(&m_pointsColor);
		ip.setInterpolation(InterpolationType::Linear);
		color = ip.interpolate(t);
	}
	if (m_colorAnimationType == ParticleAnimation::SPLINE_DYNAMIC) {
		Interpolation ip(&m_pointsColor);
		ip.setInterpolation(InterpolationType::Hermite);
		color = ip.interpolate(t);
	}

}

void Particle::setAnimationTime(float time)
{
	setAnimationTimeColor(time);
	setAnimationTimeSize(time);
}

void Particle::setAnimationTimeColor(float time)
{
	m_animationTimeColor = time;
	m_currentTimeInAnimationColor = 0;
}

void Particle::setAnimationTimeSize(float time)
{
	m_animationTimeSize = time;
	m_currentTimeInAnimationSize = 0;
}

void Particle::setAnimationBehavior(AnimationBehavior behavior)
{
	setAnimationBehaviorColor(behavior);
	setAnimationBehaviorSize(behavior);
}

void Particle::setAnimationBehaviorColor(AnimationBehavior behavior)
{
	m_animBehaviorColor = behavior;
}

void Particle::setAnimationBehaviorSize(AnimationBehavior behavior)
{
	m_animBehaviorSize = behavior;
}


glm::vec4 Particle::randomStatic(int min, int max, int divisor)
{
	max++;
	float r = (rand() % max) + min;
	float g = (rand() % max) + min;
	float b = (rand() % max) + min;
	return glm::vec4(r/divisor, g/divisor, b/divisor, 1);
}



