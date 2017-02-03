WinningScreen = {

	onAwake = function(componentId) 
	    go = scriptableComponent.getGameObjectId(componentId)
		
		trans = gameObject.getTransformComponent(go)
		transformComponent.setPosition(trans,vector2(0,0))
		sprite = gameObject.addSpriteComponent(go)
		spriteComponent.setSprite(sprite, "background")
		spriteComponent.setSortingOrder(sprite, 0)
		spriteWidth = spriteComponent.getWidth(sprite)
		spriteHeight = spriteComponent.getHeight(sprite)
		
		
		sceneName = sceneSystem.getCurrentSceneName()
		wonText = scene.addGameObject(sceneName, "Winning text")
		transform = gameObject.addTransformComponent(wonText)
		transformComponent.setPosition(transform, vector2(touchingButts.getWidth()/2-70, touchingButts.getHeight()/2+35))
		text = gameObject.addTextComponent(wonText)
		textComponent.setText(text, "You have won the game")
		
		buttonObject = scene.addGameObject(sceneName, "toMenuButton")
		buttonTransform = gameObject.addTransformComponent(buttonObject)
		transformComponent.setPosition(buttonTransform, vector2(touchingButts.getWidth()/2-70, touchingButts.getHeight()/2-35))
		button = gameObject.addButtonComponent(buttonObject)
		buttonComponent.setSprite(button,"button")
		buttonTextComponent = gameObject.getTextComponent(buttonObject)
		textComponent.setText(buttonTextComponent, "To Main Menu")
		buttonComponent.setOnClickListener(button, componentId, "toMainMenu")
	end,
	
	onStart = function(self) 
	gameManager = scene.getGameObjectIdFromName(sceneName, "gameManager")
		if(gameManager ~= -1) then
			gmScript = gameObject.getScriptableComponent(gameManager)
			if(gmScript > 0) then
				coins = scriptableComponent.callLuaFunction(gmScript, "getCoins")
				if(coins == 12) then
					textComponent.setText(text, "You have won the game!\nYou collected all the coins!")
				end
			end
		end
	end,
	
	toMainMenu = function(self) 
		gameManager = scene.getGameObjectIdFromName(sceneName, "gameManager")
		if(gameManager ~= -1) then
			gmScript = gameObject.getScriptableComponent(gameManager)
			if(gmScript > 0) then
				coins = scriptableComponent.callLuaFunction(gmScript, "setState", "MenuState")
			end
		end
		sceneSystem.activateScene("MenuScene")
	end,
}
