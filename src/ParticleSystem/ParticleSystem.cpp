#include "src/TouchingButts.hpp"
#include "ParticleSystem.h"

void ParticleSystem::setSize(int size) {
	initCheck();
	m_particles.clear();
	m_finalPos.clear();
	m_particleSize.clear();

	for (int i = 0; i<size; i++) {
		m_particles.push_back(Particle(glm::vec3{ 0,0,0 }, glm::vec3{ 0,-1,0 }, -999999));
		m_finalPos.push_back(glm::vec3{ 0,0,0 });
		m_particleSize.push_back(0.1f);
	}
}

bool ParticleSystem::init()
{
	m_mesh = nullptr;
	m_currentTime = 0;
	m_emissionIndex = 0;

	m_shader = SRE::Shader::getStandardParticles();

	//Default size = 512
	int size = 512;

	setSize(size);

	EngineSystem::init();
	initCheck();
	return true;
}

void ParticleSystem::emit(glm::vec3 position, glm::vec3 velocity) {
	initCheck();
	m_particles[m_emissionIndex].timeOfBirth = m_currentTime;
	m_particles[m_emissionIndex].position = position;
	m_particles[m_emissionIndex].velocity = velocity;
	m_emissionIndex = (m_emissionIndex + 1) % m_particles.size();
}

void ParticleSystem::animateLastEmissionColor(ParticleAnimation type, glm::vec4 color1, glm::vec4 color2, glm::vec4 color3, glm::vec4 color4)
{
	if(m_emissionIndex > 0)
		animateEmissionIndexColor(m_emissionIndex - 1, type, color1, color2, color3, color4);
}

void ParticleSystem::animateEmissionIndexColor(int index, ParticleAnimation type, glm::vec4 color1, glm::vec4 color2, glm::vec4 color3, glm::vec4 color4)
{
	m_particles[index].animateParticleColor(type, color1, color2, color3, color4);
}

void ParticleSystem::animateLastEmissionSize(ParticleAnimation type, float size1, float size2, float size3, float size4)
{
	if(m_emissionIndex > 0) 
		animateEmissionIndexSize(m_emissionIndex - 1, type, size1, size2, size3, size4);
}

void ParticleSystem::animateEmissionIndexSize(int index, ParticleAnimation type, float size1, float size2, float size3, float size4)
{
	m_particles[index].animateParticleSize(type, size1, size2, size3, size4);
}

void ParticleSystem::setLastEmissionAnimationTime(float time)
{
	if(m_emissionIndex > 0)
		setEmissionIndexAnimationTime(m_emissionIndex - 1, time);
}

void ParticleSystem::setEmissionIndexAnimationTime(int index, float time)
{
	m_particles[index].setAnimationTime(time);
}

void ParticleSystem::setLastEmissionAnimationTimeSize(float time)
{
	if (m_emissionIndex > 0)
		setEmissionIndexAnimationTimeSize(m_emissionIndex - 1, time);
}

void ParticleSystem::setLastEmissionAnimationTimeColor(float time)
{
	if (m_emissionIndex > 0)
		setEmissionIndexAnimationTimeColor(m_emissionIndex - 1, time);
}

void ParticleSystem::setEmissionIndexAnimationTimeSize(int index, float time)
{
	m_particles[index].setAnimationTimeSize(time);
}

void ParticleSystem::setEmissionIndexAnimationTimeColor(int index, float time)
{
	m_particles[index].setAnimationTimeColor(time);
}


void ParticleSystem::setLastEmissionAnimationBehavior(AnimationBehavior behavior)
{
	if (m_emissionIndex > 0)
		setEmissionIndexAnimationBehavior(m_emissionIndex - 1, behavior);
}

void ParticleSystem::setEmissionIndexAnimationBehavior(int index, AnimationBehavior behavior)
{
	m_particles[index].setAnimationBehavior(behavior);
}

void ParticleSystem::setLastEmissionAnimationBehaviorSize(AnimationBehavior behavior)
{
	if (m_emissionIndex > 0)
		setEmissionIndexAnimationBehaviorSize(m_emissionIndex - 1, behavior);
}

void ParticleSystem::setLastEmissionAnimationBehaviorColor(AnimationBehavior behavior)
{
	if (m_emissionIndex > 0)
		setEmissionIndexAnimationBehaviorColor(m_emissionIndex - 1, behavior);
}

void ParticleSystem::setEmissionIndexAnimationBehaviorSize(int index, AnimationBehavior behavior)
{
	m_particles[index].setAnimationBehaviorSize(behavior);
}

void ParticleSystem::setEmissionIndexAnimationBehaviorColor(int index, AnimationBehavior behavior)
{
	m_particles[index].setAnimationBehaviorColor(behavior);
}

void ParticleSystem::update(float deltaTime) {
	initCheck();
	std::vector<glm::vec4> colors;

	auto gravity = g_physicsSystem->getWorld()->GetGravity();
	glm::vec3 a(0, gravity.y, 0);
	for (int i = 0; i<m_finalPos.size(); i++) {
		float t = m_currentTime - m_particles[i].timeOfBirth;
		auto v0 = m_particles[i].velocity;
		auto p0 = m_particles[i].position;
		m_finalPos[i] = 0.5f*a*t*t + v0*t + p0;
		m_particles[i].update(deltaTime);
		m_particleSize[i] = m_particles[i].size;
		colors.push_back(m_particles[i].color);
	}
	// unused - using default values
	
	std::vector<glm::vec2> uvs;
	std::vector<float> uvSize;
	std::vector<float> uvRotation;

	if (m_mesh == nullptr) {
		m_mesh = new SRE::ParticleMesh(m_finalPos, colors, uvs, uvSize, uvRotation, m_particleSize);
	}
	else {
		m_mesh->update(m_finalPos, colors, uvs, uvSize, uvRotation, m_particleSize);
	}
	m_currentTime += deltaTime;
}

void ParticleSystem::render() {
	initCheck();
	SRE::SimpleRenderEngine::instance->draw(m_mesh, glm::mat4(1), m_shader);
}


void ParticleSystem::shutdown()
{
	EngineSystem::shutdown();
}

ParticleSystem::ParticleSystem()
{
	//Do nothing!
}

ParticleSystem::~ParticleSystem()
{
	//Do nothing!
}
