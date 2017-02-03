Tube = {
	onAwake = function(componentId) 
		go = scriptableComponent.getGameObjectId(componentId)
		gameObject.addBox2DColliderComponent(go)
		result = {
			id = go
		}
		return result
	end,
	
	onCollisionEnter = function(self, other)
		if(gameObject.getName(other) == "mario") then
			marioScript = gameObject.getScriptableComponent(other)
			marioTrans = gameObject.getTransformComponent(other)
			marioPos = transformComponent.getPosition(marioTrans)
			marioY = marioPos:getY()
			
			tubeTrans = gameObject.getTransformComponent(self.id)
			tubePos = transformComponent.getPosition(tubeTrans)
			tubeY = tubePos:getY()
			
			if(marioY - tubeY > 30) then
				scriptableComponent.callLuaFunction(marioScript, "enableDownTube", true)
			else
				scriptableComponent.callLuaFunction(marioScript, "enableDownTube", false)
			end
	
		end
	end,
	
	onCollisionStay = function(self, other) 
		if(gameObject.getName(other) == "mario") then
			marioScript = gameObject.getScriptableComponent(other)
			marioTrans = gameObject.getTransformComponent(other)
			marioPos = transformComponent.getPosition(marioTrans)
			marioY = marioPos:getY()
			
			tubeTrans = gameObject.getTransformComponent(self.id)
			tubePos = transformComponent.getPosition(tubeTrans)
			tubeY = tubePos:getY()
			
			if(marioY - tubeY > 30) then
				scriptableComponent.callLuaFunction(marioScript, "enableDownTube", true)
			else
				scriptableComponent.callLuaFunction(marioScript, "enableDownTube", false)
			end
	
		end
	end,
	
	checkForMarioCollision = function(self, other) 
		
			
	end,
	
	onCollisionExit = function(self, other)
		if(gameObject.getName(other) == "mario") then
			scriptableComponent.callLuaFunction(marioScript, "enableDownTube", false)
		end
	end
}