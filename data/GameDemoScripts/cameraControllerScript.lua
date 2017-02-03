CameraController = {
	onAwake = function(component) 
		--create background
		go = scriptableComponent.getGameObjectId(component)
		
		trans = gameObject.getTransformComponent(go)
		sprite = gameObject.addSpriteComponent(go)
		spriteComponent.setSprite(sprite, "background")
		spriteComponent.setSortingOrder(sprite, 0)
		spriteWidth = spriteComponent.getWidth(sprite)
		spriteHeight = spriteComponent.getHeight(sprite)
		
		transformComponent.scale(trans, vector2(touchingButts.getWidth()/spriteWidth, touchingButts.getHeight()/spriteHeight))
		result = {
			transform = trans,
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
		mario = scene.getGameObjectIdFromName(sceneSystem.getCurrentSceneName(), "mario")
		if(mario ~= -1) then
			script = gameObject.getScriptableComponent(mario)
			v = scriptableComponent.callLuaFunction(script, "getPosition", nil)
			
			if(v:getX() > self.tolorence) then
				sceneSystem.setCameraPosition(vector2(-(v:getX()-self.tolorence), 0))
				transformComponent.setPosition(self.transform, vector2(v:getX()-self.tolorence, 0))
			end
		end
	end
}