Plant = {
	onAwake = function(component) 
		goid = scriptableComponent.getGameObjectId(component)
		trans = gameObject.addTransformComponent(goid)
		anim = gameObject.addAnimation2DComponent(goid)
		animation2DComponent.addAnimation(anim, "green_plant")
		animation2DComponent.playAnimation(anim, "green_plant")

		result = {
			comp = component,
			id = goid,
			transform = trans
		}
		return result
	end,

	onStart = function(self) 
		gameObject.addRigidBodyComponent(self.id)
	end,
	
	onCollisionEnter = function(self, other) 
		if(gameObject.getName(other) == "mario") then
			sceneSystem.activateScene("MenuScene")
		end
	end
	
}