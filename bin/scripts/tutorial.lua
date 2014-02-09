dofile('scripts/standard.lua')
dofile('scripts/skrzynie.lua')
dofile('scripts/wiatraki.lua')
dofile('scripts/wiadomosci.lua')
dofile('scripts/kula.lua')
dofile('scripts/zmianaTypu.lua')
dofile('scripts/aurory.lua')
NextLevel = "introduction"
--CzasPoziomu = 60 * 7 + 1


UsuwanaPrzeszkoda = ""
AnimacjaPowitalnaStatus = false
TimeCounting = false --pomocnicza informacja, czy bariera czasu przekroczona i zmienic muzyke
--funkcja wykonywana przy starcie poziomu
function main(status)
	dofile('scripts/create.lua')
	SetPostProcessingEffect("Clean")
	AddMessage("start1", "Witaj w krótkim tutorialu!")
	AddMessage("start2", "Poruszaj kul¹ za pomoc¹ \n strza³ek na klawiaturze...")
	AddMessage("start3", "Kamerê obracasz za pomoc¹ \n poziomych ruchów myszki...")
	AddMessage("start4", "Aby zmieniæ wysokoœæ patrzenia \n wciœnij lewy przycisk myszy \n i porusz myszk¹ w pionie...")
	AddMessage("start5", "Aby ukoñczyæ tutorial \n dojdŸ do pola KONIEC")
	AddMessage("start6", "Uwa¿aj ¿eby nie wypaœæ za planszê, \n bêdziesz musia³ zacz¹æ od pocz¹tku...")
	
	
	AddMessage("outOfScene", "Wypad³eœ za planszê!\n Spróbuj ponownie...\n ")
	AddMessage("koniec", "Gratulacje! \n Ukoñczy³eœ tutorial.")
	
	AktualnaKula = "KulaDrewno"
	ResourceParseIrrXML('scripts/introduction/scena2.xml', "IrrXmlParserCallback")
	CameraSetFollowingObject(AktualnaKula)
	CameraSetStatus(Camera.follow)
	CameraDistance(10.0)
	CameraDistanceUp(5.0)
	CameraSetRotation(90.0)
	EntitySetUpdateObject(AktualnaKula, "StoneControl")
	EntityHide(KulaPapier)
	EntityHide(KulaKamien)
	SetAuroraCount(0)
	
	UruchomSmigla()
	if AktualnaKula == KulaPapier then
		AktywujWentylatory()
	else
		DeaktywujWentylatory()
	end
	EntitySetCallback("msgKoniec", "koniecPoziomu", Callback.onStartTouch)
	UaktualnijSkrzynie()
	AnimacjaPowitalna()
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


function InputSpace()
	if AnimacjaPowitalnaStatus == true then
		AnimacjaPowitalnaStatus = false
		TimerDel("AnimacjaPowitalnaStep2")
		TimerDel("AnimacjaPowitalnaStep3")
		TimerDel("AnimacjaPowitalnaStep4")
		TimerDel("AnimacjaPowitalnaStep5")
		TimerDel("AnimacjaPowitalnaStep6")
		AnimacjaPowitalnaStep7()
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
	TimerAdd("AnimacjaPowitalnaStep2", 3.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep2")
end
function AnimacjaPowitalnaStep2()
	ShowMessage(GetMessage("start2"))
	TimerAdd("AnimacjaPowitalnaStep3", 3.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep3")
end
function AnimacjaPowitalnaStep3()
	ShowMessage(GetMessage("start3"))
	TimerAdd("AnimacjaPowitalnaStep4", 3.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep4")
end
function AnimacjaPowitalnaStep4()
	--wylaczenie wiatraka
	ShowMessage(GetMessage("start4"))
	TimerAdd("AnimacjaPowitalnaStep5", 3.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep5")
end
function AnimacjaPowitalnaStep5()
	ShowMessage(GetMessage("start5"))
	TimerAdd("AnimacjaPowitalnaStep6", 3.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep6")
end
function AnimacjaPowitalnaStep6()
	ShowMessage(GetMessage("start6"))
	TimerAdd("AnimacjaPowitalnaStep7", 3.0, TimerType.simple, TimerCallback.Lua, "AnimacjaPowitalnaStep7")
end
function AnimacjaPowitalnaStep7()
	CameraSetFollowingObject(AktualnaKula)
	CameraDisableAnimation()
	CameraSetRotation(90.0)
	CameraDistance(10.0)
	CameraDistanceUp(5.0)
	SoundStop("animationBackground")
	playBallSound(AktualnaKula)
	ShowMessage("")
	--SetTimeout(CzasPoziomu)
	EntityEnableUpdateObject(AktualnaKula)
end
--[[ ###############  ANIMACJA STARTOWA KONIEC ###########################]]--
