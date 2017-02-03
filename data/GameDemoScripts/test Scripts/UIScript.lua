UI = {
	onAwake = function(componentId)
		debugSystem.writeToDebug("UI onAwake")
		sceneName = sceneSystem.getCurrentSceneName()
		go = scene.addGameObject(sceneName, "mushroomCreatorButton")
		trans = gameObject.addTransformComponent(go)
		button = gameObject.addButtonComponent(go)
		transformComponent.setPosition(trans, vector2(50, 600))
		buttonComponent.setSprite(button, "brick")
		buttonComponent.setOnClickListener(button, componentId, "spawnMushroom")
	end,
	
	spawnMushroom = function(self) 
		debugSystem.writeToDebug("Hej med dig fra Spawn Mushroom")
		sceneName = sceneSystem.getCurrentSceneName()
		go = scene.addGameObject(sceneName, "mushroom")
		script =gameObject.addScriptableComponent(go)
		scriptableComponent.loadScript(script, "data/mushroomScript.lua", "Mushroom")
	end
}