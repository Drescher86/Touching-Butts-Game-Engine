#include "ParticleDemo.h"
#include "src/TouchingButts.hpp"
#include "glm/glm.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtx/closest_point.hpp>
#include "src/Components/RigidBodyComponent.h"
#include "src/Components/Box2DColliderComponent.h"

bool ParticleDemo::update(float deltaTime) {
	g_particleSystem->emit(glm::vec3(-4.5f, 0.0f, 0.0f), glm::vec3(glm::circularRand<float>(6.0f), 0.0));
	g_particleSystem->animateLastEmissionColor(ParticleAnimation::SPLINE_DYNAMIC, glm::vec4(1, 0.f, 0.f, 1), glm::vec4(0, 1, 0, 1), glm::vec4(0, 0, 1, 1), glm::vec4(0.3, 0.3, 0.3, 1));
	g_particleSystem->animateLastEmissionSize(ParticleAnimation::SPLINE_DYNAMIC, 0.1f, .2f, 1.0f, .01f);
	g_particleSystem->setLastEmissionAnimationBehavior(AnimationBehavior::GO_BACK);
	g_particleSystem->setLastEmissionAnimationTime(1.f);
	g_particleSystem->setLastEmissionAnimationTimeColor(.5f);
	g_particleSystem->setLastEmissionAnimationTimeSize(0.8f);
	g_particleSystem->setLastEmissionAnimationBehaviorSize(AnimationBehavior::GO_BACK);
	g_particleSystem->setLastEmissionAnimationBehaviorColor(AnimationBehavior::GO_BACK);

	g_particleSystem->emit(glm::vec3(4.5f, 3.0, 1.0f), glm::vec3(glm::circularRand<float>(2.0f), 0.0));
	g_particleSystem->animateLastEmissionColor(ParticleAnimation::FIXED_STATIC, glm::vec4(0, 0, 1, 1));
	g_particleSystem->animateLastEmissionSize(ParticleAnimation::FIXED_STATIC, 0.1f);

	if (g_inputSystem->getKeyDown(KeyCode::QUIT) || g_inputSystem->getKeyDown(KeyCode::ESCAPE))
		return false;

	return true;
}

void ParticleDemo::init()
{
	g_sceneSystem->changeCameraTo3D(1280, 720);
	g_particleSystem->setSize(5000);
}
