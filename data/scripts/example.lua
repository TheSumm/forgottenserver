local actionScript = ActionScript()

function onUse(player, item, ...)
	print(player:getName())
	return true
end

print("Register", actionScript:register(1945, "onUse"))
