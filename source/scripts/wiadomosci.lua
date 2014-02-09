messages = {}

function AddMessage(name, text)
	messages[name] = text
end
function GetMessage(name)
	if messages[name] ~= nil then
		return messages[name]
	else
		return ""
	end
end