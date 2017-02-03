Tree = {
	go = 0,
	
	onAwake = function(gameObject) 
		go = gameObject
		gameObject:listenForEvent("carmoved", "onCarMovedEvent")
		return "Setting up tree functionality"
	end,
	
	onCarMovedEvent = function()
		print("Recieved event in Tree.lua that car has moved!")
	end
}