--zmienne wymagane przy zmianie typu kuli czyli nazwa aktualnej, pozycja i nazwa zmienianej
AktualnaKula = ""
Pozycja = {}
Pozycja.x = 0.0
Pozycja.y = 0.0
Pozycja.z = 0.0
ZmianaKula = "none";


function zmianaTypuKuliStart(sourceObject, callbackObject)
	if callbackObject == "KulaDrewno" or callbackObject == "KulaKamien" or callbackObject == "KulaPapierPhysX" then
		if ZmianaKula == "none" then
			local typPlatformy = string.sub(sourceObject,1,12)
			if typPlatformy == "zmianaKamien" then
				if AktualnaKula ~= "KulaKamien" then
					ZmianaKula = "KulaKamien"
				end
			elseif typPlatformy == "zmianaDrewno" then
				if AktualnaKula ~= "KulaDrewno" then
					ZmianaKula = "KulaDrewno"
				end
			elseif typPlatformy == "zmianaPapier" then
				if AktualnaKula ~= "KulaPapierPhysX" then
					ZmianaKula = "KulaPapierPhysX"
				end
			end
			if ZmianaKula ~= "none" then --jesli wykryto zmiane
				math.randomseed( os.time() )
				local nazwaTimera = "kulaZmiana" .. math.random(1,300)
				if TimerAdd(nazwaTimera, 4.0, TimerType.simple, TimerCallback.Lua, "zmianaTypuKuliEnd") then
					EntityClearForces(AktualnaKula)
					EntityDisableUpdateObject(AktualnaKula)
				else
					ZmianaKula = "none"
				end
			end
		end
	end
end
function zmianaTypuKuliEnd(n)
	Pozycja.x, Pozycja.y, Pozycja.z = EntityGetPosition(AktualnaKula)
	EntitySetStartPosition(ZmianaKula, Pozycja.x, Pozycja.y, Pozycja.z)
	EntityHide(AktualnaKula)
	EntityShow(ZmianaKula)
	CameraSetFollowingObject(ZmianaKula)
	EntitySetUpdateObject(ZmianaKula, "StoneControl")
	AktualnaKula = ZmianaKula
	ZmianaKula = "none"
	UaktualnijSkrzynie()
	SoundPlay2D("", "ballTypeChanged", SoundLoop.once)
	
	math.randomseed( os.time() )
	local nazwaTimera = "kulaZmianaMuzyka" .. math.random(1,300)
	TimerAdd(nazwaTimera, 1.0, TimerType.simple, TimerCallback.Lua, "zmianaTypuKuliEnd2")
	stopBallSound()
	
	if AktualnaKula == KulaPapier then
		AktywujWentylatory()
	else
		DeaktywujWentylatory()
	end
end
function zmianaTypuKuliEnd2(n)
	playBallSound(AktualnaKula)
end

