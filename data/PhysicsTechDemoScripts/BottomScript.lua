BottomScript = {
	
	onAwake = function(componentId) 
		go = scriptableComponent.getGameObjectId(componentId)
		gameObject.addBox2DColliderComponent(go)
	end
}