FallDownKiller = {
	
	onAwake = function(componentId) 
		go = scriptableComponent.getGameObjectId(componentId)
		gameObject.addBox2DColliderComponent(go)
		result = {
			id = go,
			trans = gameObject.getTransformComponent(go)
		}
		return result
	end,
	
	update = function(self, deltaTime)  
		mario = scene.getGameObjectIdFromName(sceneSystem.getCurrentSceneName(), "mario")
		if(mario ~= -1) then
			script = gameObject.getScriptableComponent(mario)
			v = scriptableComponent.callLuaFunction(script, "getPosition", nil)
			if(v:getX() ~= nil) then
				pos = vector2(v:getX()- 10, -32)
				if(self.trans ~= nil) then
					transformComponent.setPosition(self.trans, pos)
				else
					-- trans = gameObject.addTransformComponent(self.id)
				end
			end
		end
	end,
	
	onCollisionEnter = function(self, other)
		if(gameObject.getName(other) == "mario") then
			sceneSystem.activateScene("MenuScene")
		end
	end

}