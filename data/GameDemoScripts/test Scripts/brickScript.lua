Brick = {
	onAwake = function(componentId) 
		debugSystem.writeToDebug("compId: " .. componentId)
		objectId = scriptableComponent.getGameObjectId(componentId)
		result = { 
			spawnObject = false,
			spawnPlant = false,
			plantSpawned = false,
			comp = componentId,
			id = objectId 
		}
		gameObject.addBox2DColliderComponent(result.id);
		return result
	end,
	
	setPosition = function(self, position) 
		debugSystem.writeToDebug("position brick: " .. position:tostring())
		trans = gameObject.addTransformComponent(self.id)
		transformComponent.setPosition(trans, position)
		sprite = gameObject.addSpriteComponent(self.id)
		spriteComponent.setSprite(sprite, "brick")
		gameObject.addBox2DColliderComponent(self.id);
	end
}