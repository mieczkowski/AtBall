dofile('scripts/standard.lua')
dofile('scripts/skrzynie.lua')
dofile('scripts/wiatraki.lua')
dofile('scripts/wiadomosci.lua')
--nazwa kolejnego poziomu
NextLevel = "second"

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
--funkcja wykonywana przy starcie poziomu
function main()
	dofile('scripts/create.lua')
	AddMessage("start1", "Witaj w œwiecie AtBall SECOND!")
	AddMessage("start2", "Aby uruchomiæ wiatrak umo¿liwiaj¹cy \n przejœcie do kolejnej czêœci poziomu \n musisz zebraæ 3 Aurory.")
	AddMessage("start3", "Aby usun¹æ przeszkodê \n umo¿liwiaj¹c¹ przejœcie dalej \n musisz zebraæ 7 Auror.")
	AddMessage("start4", "Zbierz wszystkie aurory \n a ostatnia przeszkoda równie¿ zniknie.")
	AddMessage("start5", "Nie œpiesz siê...\n Masz a¿ 15 minut na przejœcie\n poziomu\n POWODZENIA!")
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
	--ZatrzymajWentylator(1, true)
	--UruchomWentylator(1, true)
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
	--Funkcja wywo³uje siê przez caly okres trwania licznika, mozna to wykorzystac np do zmiany muzyki jak zostanie 10 sekund
end
-- KONIEC POZIOMU
function Timeout()
	ShowError("KONIEC CZASU!")
end
-- ZAMKNIECIE WIADOMOSCI JESLI JAKAS OTWARTA
function InputSpace()
	--ShowError("SPACJA!")
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
		TimerAdd("OUT_OF_SCENE_ENDING", 8.0, TimerType.counting, TimerCallback.Lua, "outOfSceneEnding")
	end
end
function outOfScene2(name)
	EntityHide(name)
end
function outOfSceneEnding(t)
	--"Wypad³eœ za planszê!\n Spróbuj ponownie...\n
	if t == 0 then
		ResetGame()
	else
		local sec = math.ceil(t / 1000)
		ShowMessage("Wypad³eœ za planszê!\n Restart poziomu za " .. sec .. " sekund...")
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
	TimerAdd("END_LEVEL", 5.0, TimerType.counting, TimerCallback.Lua, "koniecPoziomu2")
end
function koniecPoziomu2(t)
	if t == 0 then
		EndGame()
	else
		local sec = math.ceil(t / 1000)
		ShowMessage("GRATULACJE!\n Ukoñczy³eœ poziom.\n £adowanie nastêpnego za: \n " .. sec .. "")
	end
end



--[[ ###############  ANIMACJA STARTOWA ###########################]]--
function AnimacjaPowitalna()
	SoundPlay2D("animationBackground", "animationBackgroundFile", SoundLoop.loop)
	CameraSetRotation(90.0)
	AnimacjaPowitalnaStep1()
end
--zatrzymanie sterowania, ustawienie kamery, pokazanie informacji startowej
function AnimacjaPowitalnaStep1()
	EntityDisableUpdateObject(AktualnaKula)
	ShowMessage(GetMessage("start1"))
	CameraFreezePosition()
	TimerAdd("AnimacjaPowitalnaStep2", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep2")
end
function AnimacjaPowitalnaStep2()
	CameraUnfreezePosition()
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
	EntitySetCallback("bariera1", "barieraOstrzezenie", Callback.onStartTouch)
	TimerAdd("AnimacjaPowitalnaStep6", 4.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep6")
end
function AnimacjaPowitalnaStep6()
	ShowMessage(GetMessage("start4"))
	CameraSetFollowingObject("bariera2")
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
	CameraDistance(6.0)
	CameraDistanceUp(3.0)
	EntitySetCallback("bariera2", "barieraOstrzezenie2", Callback.onStartTouch)
	EntitySetCallback("msgKoniec", "koniecPoziomu", Callback.onStartTouch)
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
	--
	ShowMessage(GetMessage("start5"))
	TimerAdd("AnimacjaPowitalnaStep8", 5.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep8")
end
function AnimacjaPowitalnaStep8()
	CameraDisableAnimation()
	CameraSetRotation(90.0)
	SoundStop("animationBackground")
	playBallSound(AktualnaKula)
	ShowMessage("")
	SetTimeout(60*10+1)
	EntityEnableUpdateObject(AktualnaKula)
end

--[[ ###############  ANIMACJA STARTOWA KONIEC ###########################]]--


--[[ ###############  ANIMACJA START WIATRAKA ###########################]]--

function AnimacjaStartWiatraka()
	--wylaczenie sterowania kamieniem
	CameraSetFollowingObject("1wiatrak")
	CameraSetRotation(90.0)
	CameraEnableAnimation(1.0)
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
	CameraSetRotation(0.0)
	EntityEnableUpdateObject(AktualnaKula)
end
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
	CameraSetRotation(0.0)
	EntityEnableUpdateObject(AktualnaKula)
end
--
--[[ ###############  ANIMACJA START WIATRAKA KONIEC ###########################]]--