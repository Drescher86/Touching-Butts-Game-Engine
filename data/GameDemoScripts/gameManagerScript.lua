GameManager = {
	onAwake = function(component) 
		go = scriptableComponent.getGameObjectId(component)
		if(gameObject.getTextComponent(go) == -1) then
			textComp = gameObject.addTextComponent(go)
		else
			textComp = gameObject.getTextComponent(go)
		end
		textComponent.setText(textComp, "Coins: 0")
		trans = gameObject.getTransformComponent(go)
		transformComponent.setPosition(trans, vector2(5, touchingButts.getHeight()-50))
		result = {
			coins = 0,
			level = 1,
			textId = textComp,
			state = "MenuState",
			transform = trans,
			dontDestroyOnLoad = "true"
		}
		
		return result;
	end,
	
	update = function(self, deltaTime) 
		if(self.state == "MenuState") then
			transformComponent.setPosition(self.transform, vector2(-100, 0))
		else 
			transformComponent.setPosition(self.transform, vector2(5, touchingButts.getHeight()-50))
		end
	end,
	
	collectCoin = function(self) 
		self.coins = self.coins + 1
		textComponent.setText(self.textId, "Coins: " .. self.coins)
	end,
	
	getCoins = function(self)
		return self.coins
	end,
	
	getLevel = function(self)
		return self.level
	end,
	
	setLevel = function(self, lvl) 
		self.level = lvl
	end,
	
	nextLevel = function(self) 
		self.level = self.level + 1
	end,
	
	setState = function(self, newState) 
		self.state = newState
	end
	
}