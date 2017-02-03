Mario = {
	onAwake = function(component)

		cameraController = scene.addGameObject(sceneSystem.getCurrentSceneName(), "CameraController")
		script = gameObject.addScriptableComponent(cameraController)
		scriptableComponent.loadScript(script, "data/cameraControllerScript.lua", "CameraController")	
		goId = scriptableComponent.getGameObjectId(component)
		result = {
			comp = component,
			go = goId,
			transform = gameObject.getTransformComponent(goId),
			rigidBody = gameObject.addRigidBodyComponent(goId),
			onGround = false
		}
		return result
	end,
	
	onStart = function(self) 
	end,
	
	update = function(self,deltaTime)
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
	end,
	
	myFunc = function(self,str) 
		debugSystem.writeToDebug("myFunc Called with argument: " .. str)
		transformComponent.scale(self.transform, vector2(1.2,1.2))
		gameObject.removeComponent(self.rigidBody)
		self.rigidBody = gameObject.addRigidBodyComponent(self.go)
	end,
	
	getPosition = function(self) 
		return transformComponent.getPosition(self.transform)
	end,
	
	onCollisionEnter = function(self, other) 
		self.onGround = true
	end
}

function moveLeft(self, deltaTime) 
		if(self.rigidBody ~= 0) then
			force = vector2(-500*deltaTime, 0)
			transformComponent.move(self.transform, force)
		end
	end
	
function moveRight(self, deltaTime)
	if(self.rigidBody ~= 0) then
		force = vector2(500*deltaTime, 0)
		transformComponent.move(self.transform, force)
	end
end

function jump(self)
	if(self.onGround and self.rigidBody ~= 0) then
		self.onGround = false
		force = vector2(0, 50000)
		rigidBodyComponent.addForce(self.rigidBody, force)
	end
end


