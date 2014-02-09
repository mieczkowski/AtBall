ZebraneAurory = 0
ZebranieAuroryInfo = false

function zebranieAurory(sourceObject, callbackObject)
	--sprawdzamy czy callbackObject to kula
	if IsBall(callbackObject) then
		--jesli tak, to ukrywamy obiekt source i dodajemy do licznika zebranych
		local x = 0.0
		local y = 0.0
		local z = 0.0
		x, y, z = EntityGetPosition(sourceObject)
		--SoundPlay3DPosition("", "itemTaken", SoundLoop.once, x, y, z)
		SoundPlay2D("", "itemTaken", SoundLoop.once)
		EntityHide(sourceObject)
		EntityDisableTrigger(sourceObject)
		ZebraneAurory = ZebraneAurory + 1
		SetAuroraCount(ZebraneAurory)
		--SoundPlay3DPosition(name, file, SoundLoop, x, y, z)
		if ZebranieAuroryInfo == true then
			zebranieAurory2()
		end
	end
end

