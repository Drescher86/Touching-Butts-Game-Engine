Menu = {

	onAwake = function(componentId) 
		sceneName = sceneSystem.getCurrentSceneName()
		playButton = scene.addGameObject(sceneName, "Play Button")
		transform = gameObject.addTransformComponent(playButton)
		transformComponent.setPosition(transform, vector2(touchingButts.getWidth()/2-100, touchingButts.getHeight()/2-40))
		button = gameObject.addButtonComponent(playButton)
		buttonComponent.setSprite(button, "button")
		buttonTextComponent = gameObject.getTextComponent(playButton)
		textComponent.setText(buttonTextComponent, "         Play")
		buttonComponent.setOnClickListener(button, componentId, "onPlayClick")
		debugSystem.writeToDebugChannel("Script", "Menu OnAwake() Done!")
		
	end,
	
	onStart = function(self) 
		gm = scene.getGameObjectIdFromName(sceneSystem.getCurrentSceneName(), "gameManager")
		if(gm == -1) then
			gm = scene.addGameObject(sceneSystem.getCurrentSceneName(), "gameManager")
			gameObject.addTransformComponent(gm)
			script = gameObject.addScriptableComponent(gm)
			scriptableComponent.loadScript(script, "data/GameDemoScripts/gameManagerScript.lua", "GameManager")
		end
		debugSystem.writeToDebugChannel("Script", "Menu OnStart() Done!")
	end,
	
	onPlayClick = function(self) 
		gm = scene.getGameObjectIdFromName(sceneSystem.getCurrentSceneName(), "gameManager")
		script = gameObject.getScriptableComponent(gm)
		scriptableComponent.callLuaFunction(script, "setState", "InGameState")
		scriptableComponent.callLuaFunction(script, "setLevel", 1)
		debugSystem.writeToDebugChannel("Script", "Play button clicked!")
		sceneSystem.loadScene("level1", "data/GameDemoScripts/Level1/Level1.json")
		sceneSystem.activateScene("level1")
		debugSystem.writeToDebugChannel("SceneLoader", "Scene loading complete!")
	end
}
