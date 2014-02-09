--nazwy trzech obiektów kul
KulaPapier = "KulaPapierPhysX"
KulaKamien = "KulaKamien"
KulaDrewno = "KulaDrewno"

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

