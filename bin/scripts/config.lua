--[[
PLIK KONFIGURACYJNY
]]--
dofile('scripts/standard.lua')
--[[
screenSize = X
gdzie X:
1: 800x600
2: 1024x768
3: 1280x800
4: 1280x1024
5: 1440x900
6: 1680x1050
7: 1920x1200
]]--
screenSize = 7
fullscreen = 1

--skyboxTexture = "media/textures/skybox/skybox.dds"
skyboxTexture = "media/textures/skybox/Islands.dds"
--skyboxTexture = "media/textures/skybox/EmptySpace.dds"
level = "tutorial"

--[[
Metody wywo³ywane przy kolejnych zmianach stanu gry, przydatne np do odgrywania dŸwiêku
]]--
function loadSongs()
	
	
	SoundAddFile("ballPapierBackgroundFile","media/sound/ballPapierBackground.ogg")
	SoundAddFile("ballStoneBackgroundFile","media/sound/ballStoneBackground.ogg")
	SoundAddFile("ballWoodBackgroundFile","media/sound/ballWoodBackground.ogg")
	SoundAddFile("menuBackgroundFile", "media/sound/menuBackground2.ogg")
	SoundAddFile("instructionsBackgroundFile", "media/sound/instructionsBackground.ogg")
	SoundAddFile("loadingBackgroundFile", "media/sound/loadingBackground.ogg")
	SoundAddFile("timeCountingFile", "media/sound/timeCounting.ogg")
	SoundAddFile("animationBackgroundFile", "media/sound/animationBackground.ogg")
	
	SoundAddFile("menuChangeFile", "media/sound/menuChange.wav")
	SoundAddFile("itemHide", "media/sound/itemHide.mp3")
	
	SoundAddFile("ballTypeChanged", "media/sound/ballTypeChanged.mp3")
	SoundAddFile("endGame", "media/sound/endGame.mp3")
	SoundAddFile("itemTaken", "media/sound/itemTaken1.ogg")
	SoundAddFile("endGame", "media/sound/endGame.mp3")
	SoundAddFile("messageOpen", "media/sound/messageOpen.mp3")
	SoundAddFile("messageClose", "media/sound/messageClose.mp3")
	SoundAddFile("ventStart", "media/sound/ventStart.mp3")
	SoundAddFile("ventStop", "media/sound/ventStop.mp3")
	
end
function onEngineStart()
--za³adowanie piosenek
	loadSongs()
end
function onScreen1(status)
	SoundPlay2D("menuBackground", "menuBackgroundFile", SoundLoop.loop)
end
function onMainMenu(status)
	SoundStop("instructionsBackground")
	--pauzujemy wszystkie dzwieki jesli przejscie ze stanu gry
	if status == "game" or status == "softPause" then
		SoundPauseAll()
	end
	--uruchomienie muzyki menu tylko jesli nie odtwarza (przejscie ze stanu gry lub introduction)
	if SoundIsFinished("menuBackground") then
		SoundPlay2D("menuBackground", "menuBackgroundFile", SoundLoop.loop)
	end
end
function onLoading(status)
	--podczas ³adowania zatrzymujemy muzyke menu
	--SoundStop("menuBackground")
	loadSongs()
	SoundPlay2D("loadingBackground", "loadingBackgroundFile", SoundLoop.loop)
end
function onPause(status)
	
end
function onGame(status)
	SoundStop("menuBackground")
	SoundStop("loadingBackground")
	--jesli przejscie ze stanu pauzy lub menu to wznawiamy wszystkie dzwieki
	SoundResumeAll()
end
function onEndGame()
	loadSongs()
	SoundStop("menuBackground")
	SoundStop("loadingBackground")
end
function onReset()
	loadSongs()
end
function onScreen2(status)

end
function onInstructions(status)
	SoundStop("menuBackground")
	SoundPlay2D("instructionsBackground", "instructionsBackgroundFile", SoundLoop.loop)
end
function onSoftPause(status)

end
function onClosing(status)
	SoundStop("mainBackground")
end
function onError(status)

end
function onMenuChange(status)
SoundPlay2D("", "menuChangeFile", SoundLoop.once)
end
function onMenuEnter(status)

end
if fullscreen == 0 then
	postProcessingEnable = 1
else
	postProcessingEnable = 0
end