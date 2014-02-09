dofile('scripts/standard.lua')
dofile('scripts/skrzynie.lua')
dofile('scripts/wiatraki.lua')
dofile('scripts/wiadomosci.lua')
--nazwa kolejnego poziomu
NextLevel = "bzium"
CzasPoziomu = 60 * 10 + 1

--nazwy trzech obiektów kul
KulaPapier = "KulaPapierPhysX"
KulaKamien = "KulaKamien"
KulaDrewno = "KulaDrewno"

--zmienne wymagane przy zmianie typu kuli czyli nazwa aktualnej, pozycja i nazwa zmienianej
AktualnaKula = ""
Pozycja = {}
Pozycja.x = 0.0
Pozycja.y = 0.0
Pozycja.z = 0.0
ZmianaKula = "none";

--ilosc zebranych auror
ZebraneAurory = 0

UsuwanaPrzeszkoda = ""
AnimacjaPowitalnaStatus = false
TimeCounting = false --pomocnicza informacja, czy bariera czasu przekroczona i zmienic muzyke
--funkcja wykonywana przy starcie poziomu
function main(status)
	dofile('scripts/create.lua')
	SetPostProcessingEffect("Clean")
	AddMessage("start1", "Witaj w œwiecie AtBall!")
	AddMessage("start2", "Aby uruchomiæ wiatrak umo¿liwiaj¹cy \n przejœcie do kolejnej czêœci poziomu \n musisz zebraæ 3 Aurory.")
	AddMessage("start3", "Aby usun¹æ przeszkodê \n umo¿liwiaj¹c¹ przejœcie dalej \n musisz zebraæ 7 Auror.")
	AddMessage("start4", "Zbierz wszystkie aurory \n a ostatnia przeszkoda równie¿ zniknie.")
	AddMessage("start5", "Nie œpiesz siê...\n Masz a¿ 10 minut na przejœcie\n poziomu\n POWODZENIA!")
	AddMessage("ostrzezenieBariera", "Aby przejœæ dalej musisz zebraæ\n 7 Auror!")
	AddMessage("ostrzezenieBariera2", "Aby ukoñczyæ poziom musisz zebraæ\n WSZYSTKIE Aurory!")
	AddMessage("outOfScene", "Wypad³eœ za planszê!\n Spróbuj ponownie...\n ")
	AddMessage("koniec", "Gratulacje! \n Ukoñczy³eœ pierwszy poziom AtBall.")
	
	AktualnaKula = "KulaKamien"
	ResourceParseIrrXML('scripts/introduction/scena.xml', "IrrXmlParserCallback")
	CameraSetFollowingObject(AktualnaKula)
	CameraSetStatus(Camera.follow)
	CameraDistance(10.0)
	CameraDistanceUp(5.0)
	CameraSetRotation(90.0)
	EntitySetUpdateObject(AktualnaKula, "StoneControl")
	EntityHide(KulaPapier)
	EntityHide(KulaDrewno)
	SetAuroraCount(0)
	
	UruchomSmigla()
	if AktualnaKula == KulaPapier then
		AktywujWentylatory()
	else
		DeaktywujWentylatory()
	end
	EntitySetCallback("bariera2", "barieraOstrzezenie2", Callback.onStartTouch)
	EntitySetCallback("msgKoniec", "koniecPoziomu", Callback.onStartTouch)
	EntitySetCallback("bariera1", "barieraOstrzezenie", Callback.onStartTouch)
	UaktualnijSkrzynie()
	AnimacjaPowitalna()
end

-- ODTWORZENIE TLA MUZYCZNEGO DLA KULI
function stopBallSound()
	SoundStop("ballPapierBackground")
	SoundStop("ballWoodBackground")
	SoundStop("ballStoneBackground")
end
function playBallSound(ballName)
	if TimeCounting == true then 
		return 
	end
	if ballName == KulaPapier then
		SoundPlay2D("ballPapierBackground", "ballPapierBackgroundFile", SoundLoop.loop)
	elseif ballName == KulaDrewno then
		SoundPlay2D("ballWoodBackground", "ballWoodBackgroundFile", SoundLoop.loop)
	elseif ballName == KulaKamien then
		SoundPlay2D("ballStoneBackground", "ballStoneBackgroundFile", SoundLoop.loop)
	end
end

-- WERYFIKACJA OBIEKTU KULI

-- ZMIANA TYPU KULI
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
-- ODLICZANIE CZASU...
function TimeoutCounting(miliseconds)
	local sec = math.ceil(miliseconds / 100)
	if TimeCounting == false then
		if sec < 601 then
			stopBallSound()
			SoundPlay2D("timeCounting", "timeCountingFile", SoundLoop.loop)
			TimeCounting = true
		end
	end
	
	if (sec < 601 and sec > 595) or (sec < 590 and sec > 585) or (sec < 580 and sec > 575) or (sec < 570 and sec > 565) or (sec < 560 and sec > 555) or (sec < 550 and sec > 545) then
		SetPostProcessingEffect("BW")
	else
		SetPostProcessingEffect("Clean")
	end
end
-- KONIEC POZIOMU
function Timeout()
	EntityDisableUpdateObject(AktualnaKula)
	EntityClearForces(AktualnaKula)
	SetPostProcessingEffect("BW")
	TimerAdd("OUT_OF_SCENE_ENDING2", 5.0, TimerType.counting, TimerCallback.Lua, "outOfSceneEnding")
end
-- ZAMKNIECIE WIADOMOSCI JESLI JAKAS OTWARTA
function InputSpace()
	if AnimacjaPowitalnaStatus == true then
		AnimacjaPowitalnaStatus = false
		TimerDel("AnimacjaPowitalnaStep2")
		TimerDel("AnimacjaPowitalnaStep3")
		TimerDel("AnimacjaPowitalnaStep4")
		TimerDel("AnimacjaPowitalnaStep5")
		TimerDel("AnimacjaPowitalnaStep6")
		TimerDel("AnimacjaPowitalnaStep7")
		AnimacjaPowitalnaStep8()
	end
end

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
		if ZebraneAurory == 3 then 
			AnimacjaStartWiatraka() 
		elseif ZebraneAurory == 7 then
			UsuwanaPrzeszkoda = "bariera1"
			AnimacjaUsuniecieBariery()
		elseif ZebraneAurory == 18 then
			UsuwanaPrzeszkoda = "bariera2"
			AnimacjaUsuniecieBariery()
		end
	end
end

function outOfScene(name)
	if IsBall(name) then
		--zatrzymanie pozycji kamery, i wyswietlenie info
		-- po 3 sekundach reset poziomu
		CameraFreezePosition()
		SetPostProcessingEffect("BW")
		TimerDel("SYSTEM GameTime")
		TimerAdd("OUT_OF_SCENE_ENDING", 5.0, TimerType.counting, TimerCallback.Lua, "outOfSceneEnding")
	end
end
function outOfScene2(name)
	EntityHide(name)
end
function outOfSceneEnding(t)
	--"Wypad³eœ za planszê!\n Spróbuj ponownie...\n
	SetPostProcessingEffect("BW")
	if t == 0 then
		ResetGame()
	else
		local sec = math.ceil(t / 1000)
		ShowMessage("Nie uda³o siê... :(\n Restart poziomu za " .. sec .. " sekund...")
	end
	--ResetGame()
end
-- ResetGame EndGame
function koniecPoziomu()
	EntityDisableUpdateObject(AktualnaKula)
	EntityClearForces(AktualnaKula)
	CameraEnableAnimation(1.0)
	CameraDistance(16.0)
	CameraDistanceUp(9.0)
	TimerDel("SYSTEM GameTime")
	TimerAdd("END_LEVEL", 5.0, TimerType.counting, TimerCallback.Lua, "koniecPoziomu2")
end
function koniecPoziomu2(t)
	SetPostProcessingEffect("Color")
	if t == 0 then
		EndGame()
	else
		if NextLevel == "" then
			ShowMessage("GRATULACJE!\n Ukoñczy³eœ ca³¹ grê :-)" .. sec .. "")
		else
			local sec = math.ceil(t / 1000)
			ShowMessage("GRATULACJE!\n Ukoñczy³eœ poziom.\n £adowanie nastêpnego za: \n " .. sec .. "")
		end
	end
end



--[[ ###############  ANIMACJA STARTOWA ###########################]]--
function AnimacjaPowitalna()
	AnimacjaPowitalnaStatus = true
	SoundPlay2D("animationBackground", "animationBackgroundFile", SoundLoop.loop)
	AnimacjaPowitalnaStep1()
end
--zatrzymanie sterowania, ustawienie kamery, pokazanie informacji startowej
function AnimacjaPowitalnaStep1()
	EntityDisableUpdateObject(AktualnaKula)
	CameraSetRotation(90.0)
	ShowMessage(GetMessage("start1"))
	TimerAdd("AnimacjaPowitalnaStep2", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep2")
end
function AnimacjaPowitalnaStep2()
	--CameraUnfreezePosition()
	ShowMessage(GetMessage("start2"))
	CameraSetFollowingObject("1wiatrak")
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
	CameraDistance(6.0)
	CameraDistanceUp(3.0)
	TimerAdd("AnimacjaPowitalnaStep3", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep3")
end
function AnimacjaPowitalnaStep3()
	--tylko ukrycie wiadomosci
	ShowMessage("")
	TimerAdd("AnimacjaPowitalnaStep4", 2.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep4")
end
function AnimacjaPowitalnaStep4()
	--wylaczenie wiatraka
	ZatrzymajWentylator(1, true)
	TimerAdd("AnimacjaPowitalnaStep5", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep5")
end
function AnimacjaPowitalnaStep5()
	ShowMessage(GetMessage("start3"))
	CameraSetFollowingObject("bariera1")
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
	CameraDistance(6.0)
	CameraDistanceUp(3.0)
	TimerAdd("AnimacjaPowitalnaStep6", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep6")
end
function AnimacjaPowitalnaStep6()
	ShowMessage(GetMessage("start4"))
	CameraSetFollowingObject("bariera2")
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
	CameraDistance(6.0)
	CameraDistanceUp(3.0)
	
	TimerAdd("AnimacjaPowitalnaStep7", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep7")
end
function AnimacjaPowitalnaStep7()
	--powrot do kuli i wyswietlenie ostatniej wiadomosci
	CameraSetFollowingObject(AktualnaKula)
	CameraSetRotation(180.0)
	CameraEnableAnimation(1.0)
	CameraDistance(10.0)
	CameraDistanceUp(5.0)
	CameraSetRotation(0)
	ShowMessage(GetMessage("start5"))
	TimerAdd("AnimacjaPowitalnaStep8", 5.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep8")
end
function AnimacjaPowitalnaStep8()
	CameraSetFollowingObject(AktualnaKula)
	CameraDisableAnimation()
	CameraSetRotation(90.0)
	CameraDistance(10.0)
	CameraDistanceUp(5.0)
	SoundStop("animationBackground")
	playBallSound(AktualnaKula)
	ShowMessage("")
	SetTimeout(CzasPoziomu)
	EntityEnableUpdateObject(AktualnaKula)
end

--[[ ###############  ANIMACJA STARTOWA KONIEC ###########################]]--


--[[ ###############  ANIMACJA START WIATRAKA ###########################]]--

function AnimacjaStartWiatraka()
	--wylaczenie sterowania kamieniem
	CameraSetFollowingObject("1wiatrak")
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
	CameraDistance(6.0)
	CameraDistanceUp(3.0)
	EntityClearForces(AktualnaKula)
	EntityDisableUpdateObject(AktualnaKula)
	TimerAdd("AnimacjaStartWiatrakaStep2", 1.5, TimerType.simple, TimerCallback.Lua, "AnimacjaStartWiatrakaStep2")
end
function AnimacjaStartWiatrakaStep2()
	UruchomWentylator(1, true)
	TimerAdd("AnimacjaStartWiatrakaStep3", 1.5, TimerType.simple, TimerCallback.Lua, "AnimacjaStartWiatrakaStep3")
end
function AnimacjaStartWiatrakaStep3()
	CameraSetFollowingObject(AktualnaKula)
	CameraDisableAnimation()
	CameraSetRotation(90.0)
	CameraDistance(10.0)
	CameraDistanceUp(5.0)
	EntityEnableUpdateObject(AktualnaKula)
end

--[[ ###############  ANIMACJA START WIATRAKA KONIEC ###########################]]--

function barieraOstrzezenie()
	ShowMessage(GetMessage("ostrzezenieBariera"))
	TimerAdd("barieraOstrzezenieEnd", 3.0, TimerType.simple, TimerCallback.Lua, "barieraOstrzezenieEnd")
end
function barieraOstrzezenie2()
	ShowMessage(GetMessage("ostrzezenieBariera2"))
	TimerAdd("barieraOstrzezenieEnd2", 3.0, TimerType.simple, TimerCallback.Lua, "barieraOstrzezenieEnd")
end
function barieraOstrzezenieEnd()
	ShowMessage("")
end
function AnimacjaUsuniecieBariery()
	--"bariera1"
	EntityDisableUpdateObject(AktualnaKula)
	EntityClearForces(AktualnaKula)
	CameraSetFollowingObject(UsuwanaPrzeszkoda)
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
	TimerAdd("AnimacjaUsuniecieBarieryStep2", 1.5, TimerType.simple, TimerCallback.Lua, "AnimacjaUsuniecieBarieryStep2")
end
function AnimacjaUsuniecieBarieryStep2()
	EntityHide(UsuwanaPrzeszkoda)
	SoundPlay2D("", "itemHide", SoundLoop.once)
	TimerAdd("AnimacjaUsuniecieBarieryStep3", 1.5, TimerType.simple, TimerCallback.Lua, "AnimacjaUsuniecieBarieryStep3")
end
function AnimacjaUsuniecieBarieryStep3()
	UsuwanaPrzeszkoda = ""
	CameraSetFollowingObject(AktualnaKula)
	CameraDisableAnimation()
	CameraSetRotation(90.0)
	EntityEnableUpdateObject(AktualnaKula)
end
--
