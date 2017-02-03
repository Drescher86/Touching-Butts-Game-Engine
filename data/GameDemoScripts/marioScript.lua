Mario = {
	onAwake = function(component)
		goId = scriptableComponent.getGameObjectId(component)
		
		result = {
			comp = component,
			go = goId,
			transform = gameObject.getTransformComponent(goId),
			rigidBody = gameObject.addRigidBodyComponent(goId),
			empoweredFactor = 1,
			empowered = false,
			empowerTimer = 0,
			onGround = false,
			enableDownTube = false,
			gameManagerScript = 0,
			colliders = {}
		}
		return result
	end,
	
	onStart = function(self) 
		gm = scene.getGameObjectIdFromName(sceneSystem.getCurrentSceneName(), "gameManager")
		self.gameManagerScript = gameObject.getScriptableComponent(gm)
	end,
	
	update = function(self,deltaTime)
		if(self.empowered) then
			self.empowerTimer = self.empowerTimer - deltaTime
			if(self.empowerTimer <= 0) then
				self.empowered = false
				self.empoweredFactor = 1
				transformComponent.scale(self.transform, vector2(1/(1.15),1/(1.15)))
				gameObject.removeComponent(self.rigidBody)
				self.rigidBody = gameObject.addRigidBodyComponent(self.go)
			end
		end
		pos = transformComponent.getPosition(self.transform)
		if(pos:getX() < 0) then
				rigidBodyComponent.addForce(self.rigidBody, vector2(15,0))
		end
		if(inputSystem.getKeyDown("D") and inputSystem.getKeyUp("left_shift")) then
			moveRight(self, deltaTime)
		end
		if(inputSystem.getKeyPressed("D") and inputSystem.getKeyDown("left_shift")) then
			eventSystem.fireEvent(self.go, "toggleDebugWindow")
		end
		if(inputSystem.getKeyDown("A")) then
			moveLeft(self, deltaTime)
		end
		if(inputSystem.getKeyPressed("Space")) then
			jump(self)
		end
		if(self.enableDownTube) then
			if(inputSystem.getKeyPressed("S")) then
				 curLevel = scriptableComponent.callLuaFunction(self.gameManagerScript, "getLevel") 
				 if(curLevel < 2) then
					scriptableComponent.callLuaFunction(self.gameManagerScript,"setLevel", curLevel+1)
					sceneSystem.loadScene("level"..(curLevel+1), "data/GameDemoScripts/Level"..(curLevel+1).."/Level"..(curLevel+1)..".json")
					sceneSystem.activateScene("level"..(curLevel+1))
				 else 
					 sceneSystem.loadScene("WinningScreen", "data/GameDemoScripts/WinningScreen/WinningScreen.json")
					 sceneSystem.activateScene("WinningScreen")
				 end
			end
		end
	end,
	
	enableDownTube = function(self, enable) 
		self.enableDownTube = enable
	end,

	empower = function(self) 
		
		transformComponent.scale(self.transform, vector2(1.15,1.15))
		self.empowered = true
		self.empoweredFactor = 1.25
		self.empowerTimer = 10
		gameObject.removeComponent(self.rigidBody)
		self.rigidBody = gameObject.addRigidBodyComponent(self.go)
	end,
	
	getPosition = function(self) 
		return transformComponent.getPosition(self.transform)
	end,
	
	onCollisionEnter = function(self, other) 
		if(gameObject.getName(other) == "brick" or gameObject.getName(other) == "tube") then
			otherTransform = gameObject.getTransformComponent(other)
			otherPos = transformComponent.getPosition(otherTransform)
			otherSprite = gameObject.getSpriteComponent(other)
			otherSpriteHeight = spriteComponent.getHeight(otherSprite)
			if(otherPos:getY() + (otherSpriteHeight * transformComponent.getScale(otherTransform):getY())-2 < transformComponent.getPosition(self.transform):getY()) then
				table.insert(self.colliders, other)
				self.onGround = true
			end
		end
	end,
	
	onCollisionStay = function(self, other) 
		if(gameObject.getName(other) == "brick" or gameObject.getName(other) == "tube") then
			for index, collider in pairs(self.colliders) do 
				if(collider == other) then
					return
				end
			end
			
			otherTransform = gameObject.getTransformComponent(other)
			otherPos = transformComponent.getPosition(otherTransform)
			otherSprite = gameObject.getSpriteComponent(other)
			otherSpriteHeight = spriteComponent.getHeight(otherSprite)
			if(otherPos:getY() + (otherSpriteHeight * transformComponent.getScale(otherTransform):getY())-2 < transformComponent.getPosition(self.transform):getY()) then
				table.insert(self.colliders, other)
				self.onGround = true
			end
		end
	end,
	
	onCollisionExit = function(self, other)
		toRemove = -1
		for index, collider in pairs(self.colliders) do 
			if(collider == other) then
				toRemove = index
			end
		end
		if(toRemove ~= -1) then
			table.remove(self.colliders, toRemove)
		end
		i, v = next(self.colliders)
		
		if(v == nil) then
			self.onGround = false
		end
	end
}

function moveLeft(self, deltaTime) 
		if(self.rigidBody ~= 0) then
			force = vector2(-175*deltaTime*self.empoweredFactor, 0)
			transformComponent.move(self.transform, force)
		end
	end
	
function moveRight(self, deltaTime)
	if(self.rigidBody ~= 0) then
		force = vector2(175*deltaTime*self.empoweredFactor, 0)
		transformComponent.move(self.transform, force)
	end
end

function jump(self)
	if(self.onGround and self.rigidBody ~= 0) then
		self.onGround = false
		force = vector2(0, 50000000*self.empoweredFactor)
		rigidBodyComponent.addForce(self.rigidBody, force)
	end
end


