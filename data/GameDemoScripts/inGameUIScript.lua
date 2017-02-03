InGameUI = {
	onAwake = function(componentId) 
		id = scriptableComponent.getGameObjectId(componentId)
		textComp = gameObject.addTextComponent(id)
		result = {
			textCompId = textComp,
			goId = id
		}
		return result
	end,
	
	update = function(self) 
		scene.getGameObjectWithName()
		textComponent.setText(self.textCompId, "Coins: " .. )
	end
	
}