#pragma once
#include "src/EngineSystem.h"
#include <glm/glm.hpp>
#include <SRE/ParticleMesh.hpp>
#include "Particle.h"
#include <SRE/Shader.hpp>
/**
ParticleSystem. Only works with a 3D camera.
*/
class ParticleSystem : public EngineSystem
{
public:
	/**
	Set size of particle system. Maximum amount of particles in the system.
	*/
	void setSize(int size/**Size*/);
	/**
	Emit a new particle.
	*/
	void emit(glm::vec3 position/**Position of particle.*/, glm::vec3 velocity/**Velocity of particle.*/);
	/**
	Animate the last emitted particle's color.
	*/
	void animateLastEmissionColor(ParticleAnimation type/**ParticleAnimation type.*/, glm::vec4 color1 = glm::vec4()/**Animation start color. Defaults to black.*/, glm::vec4 color2 = glm::vec4()/**Animation second color. Defaults to black.*/, glm::vec4 color3 = glm::vec4()/**Animation third color. Defaults to black.*/, glm::vec4 color4 = glm::vec4()/**Animation fourth color. Defaults to black.*/);
	/**
	Animate an emitted particle's color.
	*/
	void animateEmissionIndexColor(int index/**Index of particle.*/, ParticleAnimation type/**ParticleAnimation type.*/, glm::vec4 color1 = glm::vec4()/**Animation start color. Defaults to black.*/, glm::vec4 color2 = glm::vec4()/**Animation second color. Defaults to black.*/, glm::vec4 color3 = glm::vec4()/**Animation third color. Defaults to black.*/, glm::vec4 color4 = glm::vec4()/**Animation fourth color. Defaults to black.*/);
	/**
	Animate the last emitted particle's size.
	*/
	void animateLastEmissionSize(ParticleAnimation type/**ParticleAnimation type.*/, float size1 = 0.0f/**Animation start size. Defaults to 0.*/, float size2 = 0.0f/**Animation second size. Defaults to 0.*/, float size3 = 0.0f/**Animation third size. Defaults to 0.*/, float size4 = 0.0f/**Animation fourth size. Defaults to 0.*/);
	/**
	Animate an emitted particle's size.
	*/
	void animateEmissionIndexSize(int index/**Index of particle.*/, ParticleAnimation type/**ParticleAnimation type.*/, float size1 = 0.0f/**Animation start size. Defaults to 0.*/, float size2 = 0.0f/**Animation second size. Defaults to 0.*/, float size3 = 0.0f/**Animation third size. Defaults to 0.*/, float size4 = 0.0f/**Animation fourth size. Defaults to 0.*/);
	/**
	Set the last emitted particle's animation time.
	*/
	void setLastEmissionAnimationTime(float time/**Animation time in seconds.*/);
	/**
	Set an emitted particle's animation time.
	*/
	void setEmissionIndexAnimationTime(int index/**Index of particle.*/, float time/**Animation time in seconds.*/);
	/**
	Set the last emitted particle's size animation time.
	*/
	void setLastEmissionAnimationTimeSize(float time/**Animation time in seconds.*/);
	/**
	Set the last emitted particle's color animation time.
	*/
	void setLastEmissionAnimationTimeColor(float time/**Animation time in seconds.*/);
	/**
	Set an emitted particle' size animation time.
	*/
	void setEmissionIndexAnimationTimeSize(int index/**Index of particle.*/, float time/**Animation time in seconds.*/);
	/**
	Set an emitted particle's color animation time.
	*/
	void setEmissionIndexAnimationTimeColor(int index/**Index of particle.*/, float time/**Animation time in seconds.*/);
	/**
	Set the last emitted particle's animation behavior.
	*/
	void setLastEmissionAnimationBehavior(AnimationBehavior behavior/**AnimationBehavior type.*/);
	/**
	Set an emitted particle' animation behavior.
	*/
	void setEmissionIndexAnimationBehavior(int index/**Index of particle.*/, AnimationBehavior behavior/**AnimationBehavior type.*/);
	/**
	Set the last emitted particle's size animation time.
	*/
	void setLastEmissionAnimationBehaviorSize(AnimationBehavior behavior/**AnimationBehavior type.*/);
	/**
	Set the last emitted particle's color animation time.
	*/
	void setLastEmissionAnimationBehaviorColor(AnimationBehavior time/**AnimationBehavior type.*/);
	/**
	Set an emitted particle' size animation behavior.
	*/
	void setEmissionIndexAnimationBehaviorSize(int index/**Index of particle.*/, AnimationBehavior behavior/**AnimationBehavior type.*/);
	/**
	Set an emitted particle' color animation behavior.
	*/
	void setEmissionIndexAnimationBehaviorColor(int index/**Index of particle.*/, AnimationBehavior behavior/**AnimationBehavior type.*/);
	/**
	Update the particle system.
	*/
	void update(float deltaTime/**Time in seconds since last frame.*/);
	/**
	Render the particle system.
	*/
	void render();

	
	ParticleSystem();
	~ParticleSystem();
protected:
	virtual bool init() override;
	virtual void shutdown() override;
	friend class TouchingButts;
private:
	float m_currentTime;
	int m_emissionIndex;
	SRE::ParticleMesh* m_mesh;
	std::vector<glm::vec3> m_finalPos;
	std::vector<float> m_particleSize;
	std::vector<Particle> m_particles;
	SRE::Shader* m_shader;

	friend class TouchingButts;
};