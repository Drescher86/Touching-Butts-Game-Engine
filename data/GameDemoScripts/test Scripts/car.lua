Car = {
	go = 0,
	
	onAwake = function(gameObject) 
		go = gameObject
		gameObject:listenForEvent("left", "onLeftClick")
		gameObject:listenForEvent("right", "onRightClick")
		gameObject:listenForEvent("up", "onUpClick")
		gameObject:listenForEvent("down", "onDownClick")
		gameObject:listenForEvent("carMoved", "onCarMovedEvent")
		return "Setting up car functionality"
	end,
	
	onStart = function()
		return "Just before car's first update"
	end,
	
	update = function(deltaTime) 
		return ""
	end,
	
	onLeftClick = function() 
		go:move(-3,0,0)
	end,
	
	onRightClick = function()
		go:move(3,0,0)
		go:fireEvent("carMoved")
	end,
	
	onUpClick = function() 
		go:move(0,0,-3)
	end,
	
	onDownClick = function()
		go:move(0,0,3)
	end,
	
	onCarMovedEvent = function()
		print("Script event got fired into the event system, and is again received by the same script")
	end
}