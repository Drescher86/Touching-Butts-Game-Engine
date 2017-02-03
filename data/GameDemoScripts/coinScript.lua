Coin = {
	onAwake = function(component) 
		goid = scriptableComponent.getGameObjectId(component)
		trans = gameObject.getTransformComponent(goid)
		anim = gameObject.addAnimation2DComponent(goid)
		animation2DComponent.addAnimation(anim, "coin")
		animation2DComponent.playAnimation(anim, "coin")
		animation2DComponent.setAnimationSpeed(anim, 0.08)
		collider = gameObject.addBox2DColliderComponent(goid)
		result = {
			comp = component,
			id = goid,
			transform = trans,
			colliderId = collider
		}
		return result
	end,
	
	onStart = function(self) 
		box2DColliderComponent.setToTrigger(self.colliderId, true)
	end,
	
	onCollisionEnter = function(self, other)
		if(gameObject.getName(other) == "mario") then
			gameManager = scene.getGameObjectIdFromName(sceneSystem.getCurrentSceneName(), "gameManager")
			gmScript = gameObject.getScriptableComponent(gameManager)
			scriptableComponent.callLuaFunction(gmScript, "collectCoin")
			debugSystem.writeToDebugChannel("Physics","Coin Collected!")
			scene.removeGameObject(sceneSystem.getCurrentSceneName(), self.id)
		end
	end

}