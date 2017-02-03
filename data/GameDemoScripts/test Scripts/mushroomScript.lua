Mushroom = {
	
	onAwake = function(component) 
		result = {
			comp = component,
			id = scriptableComponent.getGameObjectId(component)
		}
		return result
	end,
	
	onStart = function(self)
		trans = gameObject.addTransformComponent(self.id)
		transformComponent.move(trans, vector2(100,108))
		anim = gameObject.addAnimation2DComponent(self.id)
		animation2DComponent.addAnimation(anim, "mushroom")
		animation2DComponent.playAnimation(anim, "mushroom")
		rigidBody = gameObject.addRigidBodyComponent(self.id)
		rigidBodyComponent.addForce(rigidBody, vector2(100, 0))
	end,
	
	onCollisionEnter = function(self, other)
		if(gameObject.getName(other) == "mario") then
			marioScript = gameObject.getScriptableComponent(other)
			scriptableComponent.callLuaFunction(marioScript, "myFunc", "hej")
			
			scene.removeGameObject(sceneSystem.getCurrentSceneName(), self.id)
		end
	end

}