#pragma once
/**
The abstract class that needs to be extended to use the Touching Butts game engine.
*/
class TouchingButtsGame {
public:
	virtual ~TouchingButtsGame() {};
	/**
	Init function called before main loop runs. Can be used to setup up initial scene.
	*/
	virtual void init() { };
	/**
	Shutdown called immediate before program is closed. Used to free up variables.
	*/
	virtual void shutdown() {};
	/**
	Main game update loop.
	*/
	virtual bool update(float deltaTime/** Time in seconds since last frame*/) = 0;
	/**
	Fixed update loop. Fixed to run 60 times a second.
	*/
	virtual void fixedUpdate(float deltaTime/**Time in seconds since last frame*/) {};
	/**
	Pre render update called immediately before rendering and after main game update loop.
	*/
	virtual void preRenderUpdate(float deltaTime/** Time in seconds since last frame*/) {};
};