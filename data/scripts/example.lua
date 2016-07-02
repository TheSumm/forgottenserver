local actionScript = ActionScript()

function actionScript.onUse(player, item, ...)
	print(player:getName())
	return true
end

actionScript:register(1945)
