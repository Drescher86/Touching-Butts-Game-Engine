MousePosition = {
	onAwake = function(component) 
		go = scriptableComponent.getGameObjectId(component)
		result = {
			textComp = gameObject.addTextComponent(go)
		}
		return result
	end,
	
	update = function(self)
		mousePos = inputSystem.getMousePosition()
		textComponent.setText(self.textComp, "("..mousePos:getX() .. ", " .. mousePos:getY() .. ")")
	end

}