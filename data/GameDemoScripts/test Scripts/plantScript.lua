Plant = {
	onAwake = function(component) 
		goid = scriptableComponent.getGameObjectId(component)
		
		gameObject.addBox2DColliderComponent(goid)
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
		
	end,
	
	move = function(self, moveTo) 
		transformComponent.move(self.transform, moveTo)
	end
	
}