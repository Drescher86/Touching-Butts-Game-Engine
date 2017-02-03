LevelFiller = {

	onAwake = function(component)
		debugSystem.writeToDebug("LevelFiller onAwake")
		for i=0,2 do
			for j=0,50 do
				brick = scene.addGameObject(sceneSystem.getCurrentSceneName(), "Brick")
				script = gameObject.addScriptableComponent(brick)
				scriptableComponent.loadScript(script, "data/brickScript.lua", "Brick")	
				scriptableComponent.callLuaFunction(script, "setPosition", vector2(j*32,0-i*32))
		    end
		end
	end
}