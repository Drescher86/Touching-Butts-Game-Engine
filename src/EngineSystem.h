#pragma once

class EngineSystem {
public:
	EngineSystem();
	~EngineSystem();
protected:
	virtual bool init();
	virtual void postInit() {};
	virtual void shutdown();
	void initCheck();
	friend class TouchingButts;
private:
	bool m_initialized;
};