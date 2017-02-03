Mushroom = {
	
	onAwake = function(component) 
		result = {
			comp = component,
			id = scriptableComponent.getGameObjectId(component)
		}
		anim = gameObject.addAnimation2DComponent(result.id)
		animation2DComponent.addAnimation(anim, "mushroom")
		animation2DComponent.playAnimation(anim, "mushroom")
		rigidBody = gameObject.addRigidBodyComponent(result.id)
		return result
	end,
	
	onStart = function(self)
		
	end,
	
	onCollisionEnter = function(self, other)
		if(gameObject.getName(other) == "mario") then
			marioScript = gameObject.getScriptableComponent(other)
			scriptableComponent.callLuaFunction(marioScript, "empower")
			scene.removeGameObject(sceneSystem.getCurrentSceneName(), self.id)
		end
	end

}