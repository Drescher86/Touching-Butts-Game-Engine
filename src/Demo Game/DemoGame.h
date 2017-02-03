#include "src/TouchingButtsGame.h"

class DemoGame : public TouchingButtsGame {
public:
	virtual bool update(float deltaTime) override;
	virtual void init() override;

	bool handleInput(float deltaTime);
private:
	bool m_firstUpdate;
};