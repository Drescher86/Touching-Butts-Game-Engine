#include "src/TouchingButtsGame.h"

class ParticleDemo : public TouchingButtsGame {
public:
	virtual bool update(float deltaTime) override;
	virtual void init() override;
private:
	bool m_firstUpdate;
};