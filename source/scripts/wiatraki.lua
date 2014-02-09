-- WIATRAKI
wentylatory = {}
smigla = {}
function DodajSmiglo(name)
	local s = {}
	local id = string.sub(name,1,1) * 1
	s.name = name
	s.rotation = {x=0, y=600.0, z=0}
	s.rotationManual = false;
	table.insert(smigla,id,s)
end
function UruchomSmigla()
	for id,smiglo in ipairs(smigla) do
		if smiglo.rotationManual == false then
			EntitySetAnimation(smiglo.name, smiglo.rotation.x, smiglo.rotation.y, smiglo.rotation.z)
		end
	end
end
function UruchomSmiglo(id)
	local name = id .. "smiglo"
	for id,smiglo in ipairs(smigla) do
		if smiglo.name == name then
			EntitySetAnimation(smiglo.name, smiglo.rotation.x, smiglo.rotation.y, smiglo.rotation.z)
			smiglo.rotationManual = false
		end
	end	
end
function ZatrzymajSmiglo(id)
	local name = id .. "smiglo"
	for id,smiglo in ipairs(smigla) do
		if smiglo.name == name then
			EntitySetAnimation(smiglo.name, 0, 0, 0)
			smiglo.rotationManual = true
		end
	end	
end
function DodajWentylator(name)
	local s = {}
	local id = string.sub(name,1,1) * 1
	s.name = name
	s.manualOn = false
	EntitySetForceField(name, 0.0, 1.0, 0.0, 150)
	table.insert(wentylatory,id,s)
end
function AktywujWentylatory()
	for id,wentylator in ipairs(wentylatory) do
		if wentylator.manualOn == false then
			EntityEnableForceField(wentylator.name)
		end
	end
end
function DeaktywujWentylatory()
	for id,wentylator in ipairs(wentylatory) do
		if wentylator.manualOn == false then
			EntityDisableForceField(wentylator.name)
		end
	end
end
function UruchomWentylator(id, playSound)
	local name = id .. "wiatrak"
	for id,wentylator in ipairs(wentylatory) do
		if wentylator.name == name then
			EntityEnableForceField(wentylator.name)
			wentylator.manualOn = false
			UruchomSmiglo(id)
			if playSound == true then
				SoundPlay2D("", "ventStart", SoundLoop.once)
			end
			if AktualnaKula == KulaPapier then
				AktywujWentylatory()
			else
				DeaktywujWentylatory()
			end
		end
	end
end
function ZatrzymajWentylator(id, playSound)
	local name = id .. "wiatrak"
	for id,wentylator in ipairs(wentylatory) do
		if wentylator.name == name then
			EntityDisableForceField(wentylator.name)
			wentylator.manualOn = true
			ZatrzymajSmiglo(id)
			if playSound == true then
				SoundPlay2D("", "ventStop", SoundLoop.once)
			end
		end
	end
end
