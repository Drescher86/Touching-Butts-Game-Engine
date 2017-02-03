CameraController = {
	onAwake = function(component) 
		result = {
			tolorence = 75
		}
		return result
	end,
	
	update = function(self, deltaTime) 
		if(inputSystem.getKeyDown("left_arrow")) then
			sceneSystem.moveCamera(vector2(200*deltaTime,0))
		end
		if(inputSystem.getKeyDown("right_arrow")) then
			sceneSystem.moveCamera(vector2(-200*deltaTime,0))
		end
		if(inputSystem.getKeyDown("down_arrow")) then
			sceneSystem.moveCamera(vector2(0, 200*deltaTime))
		end
		if(inputSystem.getKeyDown("up_arrow")) then
			sceneSystem.moveCamera(vector2(0,-200*deltaTime))
		end
		script = gameObject.getScriptableComponent(0)
		v = scriptableComponent.callLuaFunction(script, "getPosition", nil)
		
		if(v:getX() > self.tolorence) then
			sceneSystem.setCameraPosition(vector2(-(v:getX()-self.tolorence), 0))
		end
	end
}