Main = {
	onAwake = function(component)
		sceneName = sceneSystem.getCurrentSceneName()
		
		--descriptive textComponent
		textDescriptionObj = scene.addGameObject(sceneName, "text")
		textDescriptionTrans = gameObject.addTransformComponent(textDescriptionObj)
		transformComponent.setPosition(textDescriptionTrans, vector2(touchingButts.getWidth()/2-120, touchingButts.getHeight()-50))
		textDescriptionComp = gameObject.addTextComponent(textDescriptionObj)
		textComponent.setText(textDescriptionComp, "Left click buttons to set properties\nRight click on screen to create game object")
		
		-- sprite chooser button
		spriteButtonObj = scene.addGameObject(sceneName, "spriteChooserButton")
		spriteButtonTrans = gameObject.addTransformComponent(spriteButtonObj)
		transformComponent.setPosition(spriteButtonTrans, vector2(5, touchingButts.getHeight()-110))
		spriteButtonComp = gameObject.addButtonComponent(spriteButtonObj)
		buttonComponent.setSprite(spriteButtonComp,"button")
		spriteButtonText = gameObject.getTextComponent(spriteButtonObj)
		textComponent.setText(spriteButtonText, "Switch Sprite")
		buttonComponent.setOnClickListener(spriteButtonComp, component, "onSpriteChooserClick")
		
		-- collider chooser button
		colliderButtonObj = scene.addGameObject(sceneName, "colliderChooserButton")
		colliderButtonTrans = gameObject.addTransformComponent(colliderButtonObj)
		transformComponent.setPosition(colliderButtonTrans, vector2(5, touchingButts.getHeight()-210))
		colliderButtonComp = gameObject.addButtonComponent(colliderButtonObj)
		buttonComponent.setSprite(colliderButtonComp,"button")
		colliderButtonText = gameObject.getTextComponent(colliderButtonObj)
		textComponent.setText(colliderButtonText, "Switch Collider")
		buttonComponent.setOnClickListener(colliderButtonComp, component, "onColliderChooserClick")
		
		result = {
			sprite = 1,
			collider = 1,
			sprites = { "mario_1", "mushroom", "green_plant"},
			colliders = { "rigidbody", "box2D"}
		}
		return result
	end,
	
	update = function(self, deltaTime) 
		if(inputSystem.getKeyPressed("RIGHT_MOUSE_BUTTON")) then
			Main.spawnGameObject(self)
		end
	end,
	
	onSpriteChooserClick = function(self) 
		debugSystem.writeToDebug("Sprite Chooser Clicked")
		self.sprite = self.sprite + 1
		if(self.sprite > 3) then
			self.sprite = 1
		end
	end,
	
	onColliderChooserClick = function(self)
		debugSystem.writeToDebug("Collider Chooser Clicked")
		self.collider = self.collider + 1
		if(self.collider > 2) then
			self.collider = 1
		end
	end,
	
	spawnGameObject = function(self)
		go = scene.addGameObject(sceneSystem.getCurrentSceneName(), "spawnedObj")
		pos = inputSystem.getMousePosition()
		
		trans = gameObject.addTransformComponent(go)
		transformComponent.setPosition(trans, pos)
		
		sprite = gameObject.addSpriteComponent(go)
		spriteComponent.setSprite(sprite, self.sprites[self.sprite])
		
		if(self.colliders[self.collider] == "rigidbody") then
			collider = gameObject.addRigidBodyComponent(go)
		else
			collider = gameObject.addBox2DColliderComponent(go)
		end
		
	end

}







