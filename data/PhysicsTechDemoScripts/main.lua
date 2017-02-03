Main = {
	onAwake = function(component)
		
		result = {
			counter = 0,
			nameCounter = 0,
			totalObjectCounter = 0,
			x = 20,
			addedLastFrame = false,
			addedTwoFramesAgo = false,
			circleAddedLastFrame = 0,
			animId = 0,
			circleAddedTwoFramesAgo = 0
		}
		return result
	end,
	
	update = function(self, deltaTime)
		if(self.addedTwoFramesAgo) then
			circleColliderComponent.setRadius(self.circleAddedTwoFramesAgo, animation2DComponent.getHeight(self.animId)/3)
		end
		self.addedTwoFramesAgo = self.addedLastFrame
		self.circleAddedTwoFramesAgo = self.circleAddedLastFrame
		self.counter = self.counter + deltaTime
		self.addedLastFrame = false
		if(self.totalObjectCounter < 300 and self.counter >= 0.1) then
			self.addedLastFrame = true
			sceneName = sceneSystem.getCurrentSceneName()
			go = scene.addGameObject(sceneName, self.nameCounter)
			trans = gameObject.addTransformComponent(go)
			transformComponent.setPosition(trans, vector2(self.x, touchingButts.getHeight()))
			circle = gameObject.addCircleColliderComponent(go)
			circleColliderComponent.setIsDynamic(circle, true)
			self.circleAddedLastFrame = circle
			anim = gameObject.addAnimation2DComponent(go)
			self.animId = anim
			animation2DComponent.addAnimation(anim, "mushroom")
			animation2DComponent.playAnimation(anim, "mushroom")
			self.nameCounter = self.nameCounter + 1
			self.totalObjectCounter = self.totalObjectCounter + 1
			self.counter = 0
			self.x = self.x + 50
			if(self.x >= touchingButts.getWidth() - 100) then
				self.x = 35
			end
		end
	end

}







