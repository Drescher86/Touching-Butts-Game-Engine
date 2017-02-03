Touching Butts game engine
==========================

##Content

1. [Setup](#setup)
2. [Scripting](#scripting)
	1. [LUA Startup Values](#luastartup)
	2. [Lua Example Scripts](#luaexample)
	3. [Example JSON](#jsonexample)
3. [C++ functions available to LUA](#LUA)
	1. [gameObject](#gameobject)
	2. [vector2](#vector2)
	3. [sceneSystem](#scenesystem)
	4. [scene](#scene)
	5. [eventSystem](#eventsystem)
	6. [inputSystem](#inputsystem)
	7. [debugSystem](#debugsystem)
	8. [transformComponent](#transformcomponent)
	9. [spriteComponent](#spritecomponent)
	10. [rigidBodyComponent](#rigidbodycomponent)
	11. [animation2DComponent](#animation2dcomponent)
	12. [scriptableComponent](#scritablecomponent)
	13. [buttonComponent](#buttoncomponent)
	14. [textComponent](#textcomponent)
	15. [touchingButts](#touchingbutts)
	16. [box2DColliderComponent](#box2dcollidercomponent)
	17. [circleColliderComponent](#circlecollidercomponent)
4. [Available JSON fields] (#json)

Touching Butts is a 2D game engine built in C++ that allows a lot building purely from LUA scripting.

To get started build and link your game to the built .lib file. Remember to include the required DLL's in the build.

Setup<a name="setup">
-----
Extend the TouchingButtsGame abstract class as shown below.
~~~~~~~~~~~~~{.py}
#include "src/TouchingButtsGame.h"

class YourExtendedGame : public TouchingButtsGame {
public:
	virtual void fixedUpdate(float deltaTime) override;
	virtual bool update(float deltaTime) override;
	virtual void preRenderUpdate(float deltaTime) override;
	virtual void init() override;
	virtual void shutdown() {};
private:
};
~~~~~~~~~~~~~

Setup the initial scene loading in init function.

The main update loop:
~~~~~~~~~~~~~~~~~~~~~
virtual bool update(float deltaTime) override;
~~~~~~~~~~~~~~~~~~~~~

returns a boolean tellling whether the game is still running. Use this to shut down game, ie if player presses a button. It is the only function that is required to extend in order to use the game engine.

And make your main function like this:

~~~~~~~~~~~~~~~{.c}
int main(int argc, char** argv) {

	YourExtendedGame * game = new YourExtendedGame();
	int width = 1280;
	int height = 720;
    TouchingButts p(width, height, game, "Your game title");
    p.startGameLoop();
	
    return 0;
}
~~~~~~~~~~~~~~~

When run you should have a game running.

From here you can build the game with C++ and adding LUA scripts to some of them or you can build everything via LUA scripts.

Scripting <a name="scripting">
---------
---------
LUA Startup Values <a name="luastartup">
---------
The engine offers to setup some properties from a LUA script. 
To use the feature you need to have a script called tbvalues.lua placed in the same folder as the executable or as the VS/XCode project. 
The following script shows all the values that can be set from the script. You may ommit anything you do not need.
~~~~~~~~~~{.lua}
window = {
	width = 800,
	height = 600,
	fullsize = "false"
}
debug = {
	enableLuaOnTheFly = "false",
	luaUpdateTime = 0.0,
	enableDebugDraw = "false"
}
~~~~~~~~~~
Property 		  | Default Value | Description
------------------|---------------|------------
width    		  | N/A			  | The width of the game window. The value given in this file has higher priority than the one in c++ and will be used if there. Otherwise the C++ value will be used.
height   		  | N/A			  | The height of the game window. The value given in this file has higher priority than the one in c++ and will be used if there. Otherwise the C++ value will be used.
fullsize 		  | "false"		  | If the window should be fullscreen or windowed. 
enableLuaOnTheFly | "false"       | Determines if LUA scripts should be able to be updated while the game is running without restart. This includes this file. If this is set to true, and you changes any value in this script it will take effect.
luaUpdateTime 	  | 0.0			  | Time in seconds between LUA scripts are updated if enableLuaOnTheFly is set to "true". The FPS suffers a great deal if set to 0 because all LUA scripts are reloaded on every update. 1-2 seconds are usually fine.
enableDebugDraw   | "false" 	  | Set whether or not debugdraw should be enabled by default when the debug window is up opened.

Reserved Lua Functions
---------
The following functions are reserved to the engine. It is not recommended to use call them from within the scripts themselves - the engine will automatically call each of them at appropriate times.

Function Name | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
onAwake() | componentId(ID of the scriptable component) | Table of fields unique to that instance | Is called right after the component is created
onStart() | self(The table of fields unique to the instance) | void | Is called just before the first update()
update() | self(The table of fields unique to the instance), deltaTime(seconds used in last cycle) | void | Is called after the physics updates every frame - main logic updates go here
prePhysicsUpdate() |self(The table of fields unique to the instance) | void | Called before every physics update 
postPhysicsUpdate() |self(The table of fields unique to the instance) | void | Called after every physics update - just before the main update method
preRenderingUpdate() |self(The table of fields unique to the instance) | void | Called just before the renderer runs
postRenderingUpdate() |self(The table of fields unique to the instance) | void | Called just after the renderer runs
onDestroy() | self(The table of fields unique to the instance) | void | Called when the gameobject that this script is attached to is destroyed
OnCollisionEnter() | self(The table of fields unique to the instance), other(the id of the gameobject that is collided with) | void | Called on the first frame of contact between two colliders
OnCollisionStay() | self(The table of fields unique to the instance), other(the id of the gameobject that is collided with) | void | Called on every frame of contact between two colliders
OnCollisionExit() | self(The table of fields unique to the instance), other(the id of the gameobject that is collided with) | void | Called on the first frame that two colliders are not in contact anymore

Lua Example Scripts <a name="luaexample">
----------
The following is an example of creating a simple menu scene with a play button that loads another scene using LUA scripting and an example of a player character script.

~~~~~~~~~~~~~{.lua}
Menu = {
	onAwake = function(componentId) 
		sceneName = sceneSystem.getCurrentSceneName()
		playButton = scene.addGameObject(sceneName, "Play Button")
		transform = gameObject.addTransformComponent(playButton)
		transformComponent.setPosition(transform, vector2(touchingButts.getWidth()/2-100, touchingButts.getHeight()/2-40))
		button = gameObject.addButtonComponent(playButton)
		buttonComponent.setSprite(button, "button")
		buttonTextComponent = gameObject.getTextComponent(playButton)
		textComponent.setText(buttonTextComponent, "Play")
		buttonComponent.setOnClickListener(button, componentId, "onPlayClick")
	end,
	
	onPlayClick = function(self) 
		debugSystem.writeToDebugChannel("GUI", "Play button clicked!")
		sceneSystem.loadScene("level1", "data/level1.json")
		sceneSystem.activateScene("level1")
	end
}
~~~~~~~~~~~~~
~~~~~~~~~~~~~{.lua}
Player = {
	onAwake = function(component)
		goId = scriptableComponent.getGameObjectId(component)
		result = {
			comp = component,
			go = goId,
			rigidBody = gameObject.addRigidBodyComponent(goId),
			onGround = false
		}
		return result
	end,
	
	update = function(self,deltaTime)
		if(inputSystem.getKeyDown("D")) then
			moveRight(self, deltaTime)
		end
		if(inputSystem.getKeyDown("A")) then
			moveLeft(self, deltaTime)
		end
		if(inputSystem.getKeyPressed("Space")) then
			jump(self)
		end
	end,
	
	onCollisionEnter = function(self, other) 
		self.onGround = true
	end,
}

function moveLeft(self, deltaTime) 
	force = vector2(-175*deltaTime, 0)
	rigidBodyComponent.addForce(self.rigidBody, force)	
end
	
function moveRight(self, deltaTime)
	force = vector2(175*deltaTime, 0)
	rigidBodyComponent.addForce(self.rigidBody, force)
end

function jump(self)
	if(self.onGround) then
		self.onGround = false
		force = vector2(0, 500)
		rigidBodyComponent.addForce(self.rigidBody, force)
	end
end
~~~~~~~~~~~~~
##Example JSON <a name="jsonexample">
Sprite loading JSON
~~~~~~~~~~~~~{.json}
{
	"frames": [
	{
		"filename": "background",
		"frame": {"x":0,"y":0,"w":1032,"h":774},
		"pivot": {"x":0.5,"y":0.5}
	}],
	"meta": {
		"image": "Background.png",
		"size": {"w":1032,"h":774},
		"scale": "1"
		}
}

~~~~~~~~~~~~~
Scene loading JSON
~~~~~~~~~~~~~{.json}
{
	  "meta": [
		{
			"spriteAtlasJsonDir":"data/Images",
			"spriteAtlasJsonFile":"MarioPacked.json"
		}
	  ],
	  "gameobjects": [
	  	{
		  "uniqueId": 0,
		  "name": "mario",
		  "animations": [
			{
			  "animationName" : "mario_8"
			}
		  ],
		  "color": [ 1, 1, 1, 1 ],
		  "position": [ 10, 40, 0 ],
		  "rotationEuler": [ 0, 0, 0 ],
		  "scale": [ 1, 1, 1 ],
		  "parentId": -1,
		  "script": "data/GameDemoScripts/marioScript.lua",
		  "scriptTable": "Mario"
		},
		{
		  "uniqueId": 1,
		  "name": "brick",
		  "spriteName": "brick",
		  "color": [ 1, 1, 1, 1 ],
		  "position": [ 0, 0, 0 ],
		  "rotationEuler": [ 0, 0, 0 ],
		  "scale": [ 1, 1, 1 ],
		  "parentId": -1,
		  "script": "data/GameDemoScripts/brickScript.lua",
		  "scriptTable": "Brick"
		}
	]
}

~~~~~~~~~~~~~


C++ functions available to LUA <a name="LUA">
---------
---------
###gameObject <a name="gameobject">

functions on gameObject

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
gameObject.getName | GameObjectId: int | name: string | Get the name of the game object with the given ID
gameObject.addTransformComponent | GameObjectId: int | transformComponentId: int | Adds a transform component to the gameobject with the given ID
gameObject.addScriptableComponent | GameObjectId: int | scriptableComponentId: int | Adds a scriptable component to the gameobject with the given ID
gameObject.addSpriteComponent | GameObjectId: int | spriteComponentId: int | Adds a sprite component to the gameobject with the given ID
gameObject.addRigidBodyComponent | GameObjectId: int | rigidBodyComponentId: int | Adds a rigidBody component to the gameobject with the given ID
gameObject.addBox2DColliderComponent | GameObjectId: int | box2DColliderComponentId: int | Adds a box2DCollider component to the gameobject with the given ID
gameObject.addCircleColliderComponent | GameObjectId: int | circleColliderComponentId: int | Adds a circleCollider component to the gameobject with the given ID
gameObject.addAnimation2DComponent | GameObjectId: int | animation2DComponentId: int | Adds a animation2D component to the gameobject with the given ID
gameObject.addButtonComponent | GameObjectId: int | buttonComponentId: int | Adds a button component to the gameobject with the given ID. NOTE: Creating a buttoncomponent also adds a TextComponent that you can access and use.
gameObject.addTextComponent | GameObjectId: int | textComponentId: int | Adds a text component to the gameobject with the given ID
gameObject.getTransformComponent | GameObjectId: int | transformComponentId: int | Get the ID of the transform component attached to the gameobject with the given ID
gameObject.getScriptableComponent | GameObjectId: int | scriptableComponentId: int | Get the ID of the scriptable component attached to the gameobject with the given ID
gameObject.getSpriteComponent | GameObjectId: int | spriteComponentId: int | Get the ID of the text sprite attached to the gameobject with the given ID
gameObject.getRigidBodyComponent | GameObjectId: int | rigidBodyComponentId: int | Get the ID of the rigidBody component attached to the gameobject with the given ID
gameObject.getBox2DColliderComponent | GameObjectId: int|box2DColliderComponentId: int | Get the ID of the box2DCollider component attached to the gameobject with the given ID
gameObject.getCircleColliderComponent | GameObjectId: int | circleColliderComponentId: int | Get the ID of the circleCollider component attached to the gameobject with the given ID
gameObject.getAnimation2DComponent | GameObjectId: int | animation2DComponentId: int | Get the ID of the animation2D component attached to the gameobject with the given ID
gameObject.getButtonComponent | GameObjectId: int | buttonComponentId: int | Get the ID of the button component attached to the gameobject with the given ID
gameObject.getTextComponent | GameObjectId: int | textComponentId: int | Get the ID of the text component attached to the gameobject with the given ID
gameObject.getParent | GameObjectId: int | parentGameObjectId: int | Get the ID of the parent game object of the game object with the given ID
gameObject.removeComponent | GameObjectId: int | textComponentId: int | Adds a text component to the gameobject with the given ID

###vector2 <a name="vector2">

functions on vector2 

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
vector2 | x:float, y:float | vector2 | Constructor
tostring | N/A | string | Gets a string representatio of the vector2
getX | N/A | x: float | Gets the x value of a vector2
getY | N/A | y: float | Gets the y value of a vector2
	
###sceneSystem <a name="scenesystem">

functions on sceneSystem 

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
sceneSystem.loadScene | sceneName:string, jsonFilePath:string | void | Loads a scene from a json file into the scene system - ready to be activated later
sceneSystem.activateScene | sceneName:string | void | Activates an already loaded scene with the given sceneName
sceneSystem.getCurrentSceneName | N/A | sceneName:string | Gets the name of the current scene
sceneSystem.moveCamera | moveVector: vector2 | void | Move the camera with a vector2
sceneSystem.setCameraPosition | positionVector:vector2 | void | Set the cameras position from a vector2

###scene <a name="scene">
functions on scene 

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
scene.addGameObject | sceneName:string, gameObjectName:string | gameObjectId: int | Adds a new game object to the scene with the given name
scene.removeGameObject | sceneName:string, gameObjectId:int | successful: bool | Removes a gameobject from a scene
scene.getSize | sceneName:string|numberOfGameObject:int | Gets the number of objects in the scene given
scene.getGameObjectIdFromName | sceneName:string, objectName:string | gameObjectId:int | Retrieves the id of the first gameobject in the given scene that matches the name

###eventSystem <a name="eventsystem">
functions on eventSystem 

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
eventSystem.fireEvent | senderObjectId: int, eventName:string | void | Fires an event with a given name. senderObjectId should be the gameObjectId of the sender
eventSystem.listenForEvent | listenerId:int, eventName:string, method:string | void | Listens for an event, listener ID is the id of the scriptableComponent that listens for the event, the eventName is the event to listen for, and method is the method that should be called when the event is fired

###inputSystem <a name="inputsystem">

functions on inputSystem 

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
inputSystem.getKeyUp | keyCode: string | bool | Returns true if the key is up, false otherwise
inputSystem.getKeyDown | keyCode: string | bool | Returns true if the key is down, false otherwise
inputSystem.getKeyPressed | keyCode: string | bool | Returns true if the key was pressed this frame, false otherwise
inputSystem.getKeyReleased | keyCode: string | bool | Returns true if the key was released this frame, false otherwise
inputSystem.getMousePosition | N/A|mousePosition: vector2 | Get a vector2 corresponding to the mouseposition adjusted by the camera position
inputSystem.getWheelY | N/A | wheelY: float | Get the value of the wheel in the Y direction

###debugSystem <a name="debugsystem">

functions on debugSystem 

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
debugSystem.writeToDebug | message: string | void | Write to the General debug channel
debugSystem.writeToDebugChannel | channel:string, message:string | void | Writes to the given debug channel 
debugSystem.createDebugFile | filename:string | void | Creates and opens a debug file that are also written to everytime the console gets written to. If a file is open already, it closes and opens the new one to use
debugSystem.addChannelFilter | filter:string | void|Adds a channel filter - only channels in the filter will get written
debugSystem.removeChannelFilter | filter:string | void | Removes a channel filter

###transformComponent <a name="transformcomponent">

functions on transformComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
transformComponent.move | transformId: int, moveVector: vector2 | void | moves the transform with the given ID by the given vector
transformComponent.rotate | transformId: int, rotation:float | void | Rotates the transform with the given ID around the z axis 
transformComponent.scale | transformId: int, scaleVector:vector2 | void | Scales the transform with the given ID with the given vector
transformComponent.setPosition | transformId: int, position:vector2 | void|Set the position of the transform with the given ID
transformComponent.getPosition | transformId: int|position: vector2 | Gets the position vector of the transform with the given ID
transformComponent.getRotationAroundZAxis | transformId: int | rotation: float | Gets the rotation around the Z-axis for the transform with the given ID
transformComponent.getScale | transformId: int | scale: vector2 | Gets the scale vector of the transform with the given ID

###spriteComponent

functions on spriteComponent <a name="spritecomponent">

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
spriteComponent.getWidth | spriteId: int | width:int | Get the width of the sprite with the given ID
spriteComponent.getHeight | spriteId: int | height:int | Get the height of the sprite with the given ID
spriteComponent.setSprite | spriteId: int, spriteName:string | void | Set the sprite of the spriteComponent with the givenID to the sprite with the given name
spriteComponent.setSortingOrder | spriteId: int, sortingOrder:int | void | Set the sorting order of the spriteComponent which is used when drawing

###rigidBodyComponent

functions on rigidBodyComponent <a name="rigidbodycomponent">

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
rigidBodyComponent.addForce | rigidBodyId: int, forceVector:vector2 | width:int | Add force to the rigidbody
rigidBodyComponent.addImpulse | rigidBodyId: int, impulseVector:vector2 | height:int | Add impulse to the rigidbody
rigidBodyComponent.setVelocity | rigidBodyId: int, velocityVector:vector2 | void | Set the linear velocity of the rigidbody
rigidBodyComponent.getVelocity | rigidBodyId: int | void | Gets the velocity of the rigidBody
rigidBodyComponent.setToTrigger | rigidBodyId: int, trigger:bool | void | Set the if the body should be a trigger, default is false

###animation2DComponent <a name="animation2dcomponent">

functions on animation2DComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
animation2DComponent.getWidth | animationId: int | width:int | Get the width of the sprit
animation2DComponent.getHeight | animationId: int | height:int | Get the height of the sprite
animation2DComponent.addAnimation | animationId: int, animationName:string | void | Add an animation to the component
animation2DComponent.playAnimation | animationId: int, animationName:string | void | Play the animation with the given name
animation2DComponent.setAnimationSpeed | animationId: int, animationSpeed:float | void | Set the speed of the animation playing

###scriptableComponent <a name="scritablecomponent">

functions on scriptableComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
scriptableComponent.getGameObjectId | componentId: int|width:int | Get the width of the sprit
scriptableComponent.callLuaFunction | componentId: int, method:string, arguments:... | ... | Call a function in a given lua script, with the arguments passed and get whatever that function returns back
scriptableComponent.loadScript | componentId: int, fileName:string, tableName:string | void | Loads the script from the given file with the given table on the given component

###buttonComponent <a name="buttoncomponent">

functions on buttonComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
buttonComponent.setSprite | componentId: int, spriteName:string | void | Set the sprite of the button
buttonComponent.setOnClickListener | componentId: int, scriptableComponentId:int, method:string | void | Sets a on click listener on the button with the componentID, when clicked it calls the method given on the scriptComponent with the Id given


###textComponent <a name="textcomponent">

functions on textComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
textComponent.setText | componentId: int, text:string|void|Set the text

###touchingButts <a name="touchingbutts">

functions on touchingButts

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
touchingButts.getWidth | N/A | width:int | Get the width of the window
touchingButts.getHeight | N/A | height:int | Get the height of the window

###box2DColliderComponent <a name="box2dcollidercomponent">

functions on box2DColliderComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
box2DColliderComponent.setToTrigger | componentId:int, isTrigger:bool | void | Set whether the collider should be a trigger or not
box2DColliderComponent.setIsDynamic | componentId:int, isDynamic:bool | void | Set whether the collider should be dynamic (affected by forced) or not

###circleColliderComponent <a name="circlecollidercomponent">

functions on circleColliderComponent

Function Call | Parameters | Return Value| Description
--------------|------------|-------------|-------------------
circleColliderComponent.setToTrigger | componentId:int, isTrigger:bool | void | Set whether the collider should be a trigger or not
circleColliderComponent.setIsDynamic | componentId:int, isDynamic:bool | void | Set whether the collider should be dynamic (affected by forced) or not
circleColliderComponent.setRadius | componentId:int, radius:float | void | Set the radius of the circle collider


		
Available JSON fields <a name="json">
---------------------
---------------------


JSON name | Parent JSON | Explanation
----------|-------------|-----------------
meta	  | None        | list of meta data objects
spriteAtlasJsonDir | meta | relative path to sprite atlas' json file
spriteAtlasJsonFile | meta | name of json file
image | meta | Name of image file with relative path and extension. Format RGBA8888 expected.
size | meta | object that speficies size of image
w | size | width of image
h | size | height of image
scale | meta | scale of image
frames | None | list of Frame Objects
filename | Frame Object | name of sprite/animation
frame | Frame Object | frame object
x | frame | left x value of Frame Object on image
y | frame | top y value of Frame Object on image
w | frame | width of Frame Object on image
h | frame | height of Frame Object on image
gameobjects | None | list of Game Objects
uniqueId | Game Object | Int ID that is unique for the current scene
name | Game Object | Name of game object
animations | Game Object | List of animation names. Do not use this and spriteName on same object
animationName | animations | Name of animation
color | Game Object | list of 4 floats representing color from 0-1
position | Game Object | list of 3 ints representing position in 3D space
rotationEuler | Game Object | list of 3 ints representing rotation on 3 axis in radians
scale | Game Object | list of 3 number representing scaling on 3 axis
parentId | Game Object | uniqueId of parent, -1 if no parent
script | Game Object | name of script with relative path and extension
scriptTable | Game Object | LUA script table name
spriteName | Game Object | Name of sprite. Do not use this and animations on same object

Remember to have one root object containing any of the parentless lists.