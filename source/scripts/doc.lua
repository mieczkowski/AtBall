--[[
http://www.lua.org/pil/ - dokumentacja jezyka
/**************************/
RESOURCE
/**************************/

ResourceAddTexture(nazwa, sciezka do pliku) Dodaje teksture do managera, zwraca true lub false
ResourceAddMesh(nazwa, sciezka do pliku) Dodaje mesha do managera, zwraca true lub false
ResourceDelTexture(nazwa) Usuwa teksture
ResourceDelMesh(nazwa) Usuwa mesha
ResourceParseIrrXML(nazwaPliku, nazwaFunkcjiZwrotnej)

/**************************/
ENTITY
/**************************/

EntityCreate(nazwa, typ) Tworzy obiekt o danej nazwie (tylko dodaje do mened¿era obiektow), drugi parametr okresla typ obiektu (np zwykly, normal map itp)
EntityDelete(nazwa) Usuwa obiekt z mened¿era i wszystkie zwi¹zane z nim informacje
EntitySetStartPosition(nazwa, x, y, z) Ustawia pozycje startow¹
EntitySetStartRotation(nazwa, x, y, z) Ustawia rotacje startowa (w katach)
EntityGetPosition(nazwa) Zwraca 3 parametry [x, y, z] lub false jeœli obiekt nie istnieje
EntitySetPhysxShape(nazwa, PhysxShape) Ustawia kszta³t obiektu
EntityGetPhysxShape(nazwa) Zwraca numer kszta³tu PhysxShape
EntitySetMesh(nazwa, nazwaMesha) Ustawia mesha dla obiektu entity i tworzy aktora physxowego oraz dodaje do sceny
EntitySetTexture(nazwa, nazwaTekstury) Ustawia teksture

EntitySetForceField(nazwa, kierunekX, kierunekY, kiedynekZ, sila) Dodaje pole silowe z zadanym kierunkiem i sila
EntityEnableForceField(nazwa) Uaktywnia istniejace pole silowe
EntityDisableForceField(nazwa) Deaktywuje istniejace pole silowe

EntityEnableUpdateObject(nazwa)
EntityDisableUpdateObject(nazwa)

EntityShow(nazwa) - pokazuje obiekt
EntityHide(nazwa) - ukrywa obiekt

EntitySetBindObject(nazwa, nazwaObiektu) £¹czy dwa obiekty, z czego pierwszy reprezentuje kszta³t w physxie, drugi reprezentuje widzialny obiekt
/************** Poni¿sze funkcje SET przyjmuj¹ dwa parametry (nazwa, float) i ustawiaj¹ podan¹ wartoœæ
/************** funkcje GET przyjmuj¹ jeden parametr (nazwa) i zwracaj¹ float jako wartoœæ lub false jeœli nie mo¿na pobraæ (np aktor nie istnieje)

EntitySetActorAngularDamping 
EntityGetActorAngularDamping 
EntitySetActorMaxAngularVelocity 
EntityGetActorMaxAngularVelocity 
EntitySetActorMass 
EntityGetActorMass 
EntitySetMaterialRestitution 
EntityGetMaterialRestitution 
EntitySetMaterialStaticFriction 
EntityGetMaterialStaticFriction 
EntitySetMaterialDynamicFriction 
EntityGetMaterialDynamicFriction
/**************

EntityRaiseBodyFlag(nazwa, BodyFlag) Ustawia podana flage obiektowi
EntityClearBodyFlag(nazwa, BodyFlag) Usuwa flage z obiektu

EntitySetCallback(nazwa, nazwaFunkcji, Callback) Rejestruje metode, która zostanie wykonana po wyst¹pieniu zdarzenia podanego w parametrze Callback
Przyk³ad:
EntitySetCallback("stone", "stoneStartTouch", Callback.onStartTouch)

UWAGA: metoda przyjmuje dwa parametry - nazwe obiektu ktorego dotyczy zdarzenie, oraz nazwe obiektu z ktorym nastapilo zdarzenie; 
przyklad:
function stoneStartTouch(sourceObject, callbackObject)
	ShowError("Wejscie w kontakt obiektu " .. sourceObject .. " z obiektem :" .. callbackObject)
	--za pomoca 'ent' mozemy np dokonac modyfikacji tego obiektu np:
	EntitySetTexture(sourceObject, "teksturaPoKolizji")
end

EntitySetUpdateObject(nazwa, nazwaKlasy) Przypisujemy do jednostki obiekt, ktory bedzie uaktualniac jednostke (przyklady: sterowanie kamienia, animacja, zmiana wygladu/tekstury itp)

/**************************/
SOUND
/**************************/

SoundAddFile(nazwa, sciezka do pliku) Dodaje plik do managera dzwieku (wlasciwie jest to jedynie alias do pliku, zadne fizyczne ladowanie pliku nie nastepuje)

SoundDeleteFile(nazwa) Usuwa plik z managera

/************** Ponizsze funkcje przyjmuja parametry:
/************** name:
/**************  a) jesli nazwa zostanie podana, bedzie mozliwosc pozniejszej interakcji z dzwiekiem (pauza, zatrzymanie, sprawdzenie czy gra)
/**************  b) jesli nazwa zostanie ustawiona na "" (pusta) to dzwiek bedzie odegrany ale nie bedzie utworzony dla niego obiekt (nie bedzie mozna nic z nim zrobic)
/**************  w przypadku b) nalezy uwazac podczas ustawiania parametru SoundLoop.loop, poniewaz NIE BEDZIE MOZNA ZATRZYMAC DZWIEKU PODCZAS GRY
/************** file:
/************** nazwa ustawiona przez funkcje SoundAddFile()
/**************
/************** UWAGA:
/************** W wiekszosci przypadkow uzywana bedzie wersja bez podawania nazwy, i z parametrem SoundLoop.once
/************** np odegranie dzwieku uderzenia
/************** name ustawiac jedynie wtedy kiedy odgrywamy np dluzszy dzwiek np wiadomosc glosowa lub tymczasowa muzyke
/************** i chcemy miec mozliwosc jej wylaczenia, zapauzowania itp
/************** lub jesli ustawiamy dzwiek ktory ma podazac za obiektem (np odglos turlania)
/************** Podazanie za obiektem dziala TYLKO jesli ustawimy nazwe (obiekt dzwieku wtedy uaktualnia sie)

SoundPlay2D(name, file, SoundLoop) Odgrywa dzwiek w 2D, trzeci parametr okresla czy dzwiek ma byc zapetlony czy zagrany raz

SoundPlay3DPosition(name, file, SoundLoop, x, y, z) Odgrywa dzwiek na podanej pozycji w 3D

SoundPlay3DObject(name, file, SoundLoop, nazwa obiektu, SoundPosition) Odgrywa dzwiek na pozycji podanego w 4 parametrze obiektu. 
Piaty parametr okresla czy dzwiek ma zatrzymac sie na pozycji obiektu, czy uaktualniac pozycje przy zmianie pozycji obiektu

/************** Ponizsze funkcje przyjmuja nazwe dzwieku
/************** zwracaja true jesli obiekt istnieje (i wykonano dana operacje)
/************** zwraca false jesli obiekt nie istnieje
SoundStop(nazwa)
Zatrzymuje dzwiek 
SoundStopLoop(nazwa)
SoundPause(nazwa)
SoundResume(nazwa)
SoundIsPlaying(nazwa)
Zwraca true lub false

SoundIsFinished(nazwa)
Zwraca true lub false

/**************************/
GAME
/**************************/

ShowError(tekst) 
ShowInfo(tekst) 
EndGame() - DO ZROBIENIA
NextLevel(nazwa pliku) - DO ZROBIENIA

/**************************/
CAMERA
/**************************/

CameraSetFollowingObject(nazwa) Ustawia obiekt ktory sledzic bedzie kamera (ale nie uaktywnia kamery dynamicznej!)

CameraSetStatus(Camera) Ustawia status kamery (statyczna lub dynamiczna - podazajaca za obiektem)

]]--









--[[
function CreatePlane(name, x, y, z, mesh, texture)
	if EntityCreate(name, EntityType.physx) then
		EntitySetStartPosition(name, x, y, z)
		EntitySetPhysxShape(name, PhysxShape.box)
		if EntitySetMesh(name, mesh) then
			EntitySetTexture(name, texture)
			EntitySetActorAngularDamping(name, 1.0)
			EntitySetActorMaxAngularVelocity(name, 10.0)
			EntitySetMaterialRestitution(name, 0.5)
			EntitySetMaterialStaticFriction(name, 0.5)
			EntitySetMaterialDynamicFriction(name, 0.9)
			EntityRaiseBodyFlag(name, BodyFlag.kinematic)
			return true
		else
			ShowError("LUA: Nie mozna zaladowac mesha do obiektu " .. name .. ": " .. mesh)
			return false
		end
	else
		ShowError("LUA: Nie mozna stworzyc entity: " .. name)
		return false
	end
end

function CreateTerrain(name, x, y, z, mesh, texture)
	if EntityCreate(name, EntityType.physx) then
		EntitySetStartPosition(name, x, y, z)
		EntitySetPhysxShape(name, PhysxShape.triangle)
		EntitySetDynamic(name, EntityDynamic.static)
		if EntitySetMesh(name, mesh) then
			EntitySetTexture(name, texture)
			EntitySetActorAngularDamping(name, 1.0)
			EntitySetActorMaxAngularVelocity(name, 10.0)
			EntitySetMaterialRestitution(name, 0.1) --ilosc energii po odbiciu (odbijanie sie od obiektu)
			EntitySetMaterialStaticFriction(name, 0.7) --sila miedzy obiektami statycznymi
			EntitySetMaterialDynamicFriction(name, 0.7) --sila miedzy obiektami w ruchu
			EntityRaiseBodyFlag(name, BodyFlag.kinematic)
			return true
		else
			ShowError("LUA: Nie mozna zaladowac mesha do obiektu " .. name .. ": " .. mesh)
			return false
		end
	else
		ShowError("LUA: Nie mozna stworzyc entity: " .. name)
		return false
	end
end

function CreateStone(name, x, y, z, shape, mesh, texture)
	if EntityCreate(name, EntityType.physx) then
		EntitySetStartPosition(name, x, y, z)
		EntitySetPhysxShape(name, shape)
		if EntitySetMesh(name, mesh) then
			EntitySetTexture(name, texture)
			EntitySetActorAngularDamping(name, 1.0)
			EntitySetActorMaxAngularVelocity(name, 10.0)
			EntitySetActorMass(name, 40.0)
			EntitySetMaterialRestitution(name, 0.15)
			EntitySetMaterialStaticFriction(name, 0.9)
			EntitySetMaterialDynamicFriction(name, 0.8)
			return true
		else
			ShowError("LUA: Nie mozna zaladowac mesha do obiektu " .. name .. ": " .. mesh)
			return false
		end
	else
		ShowError("LUA: Nie mozna stworzyc entity: " .. name)
		return false
	end
end
]]--

--[[
function CreateStoneBall(name, posX, posY, posZ, rotX, rotY, rotZ)
	if CreateEntity(name, posX, posY, posZ, rotX, rotY, rotZ, "Kula_Kamien", PhysxShape.sphere, EntityType.physxNormalMap, "Kula_Kamien", "Kula_KamienNormal") then
		EntitySetActorAngularDamping(name, 1.0)
		EntitySetActorMaxAngularVelocity(name, 10.0)
		EntitySetActorMass(name, 30.0)
		EntitySetMaterialRestitution(name, 0.10)
		EntitySetMaterialStaticFriction(name, 0.5)
		EntitySetMaterialDynamicFriction(name, 0.5)
		--EntityRaiseBodyFlag(name, BodyFlag.kinematic)
		--ewentualne callbacki
	else
		ShowError("LUA: Nie mozna stworzyc StoneBall: " .. name)
		return false
	end
end
function CreateBox(name, posX, posY, posZ, rotX, rotY, rotZ, model)
	local name = CreateEntity(name, posX, posY, posZ, rotX, rotY, rotZ, model, PhysxShape.triangle, EntityType.physxNormalMap, "Inne", "InneNormal")
	if name ~= false then
		EntitySetActorAngularDamping(name, 1.0)
		EntitySetActorMaxAngularVelocity(name, 10.0)
		EntitySetActorMass(name, 30.0) --masa
		EntitySetMaterialRestitution(name, 0.10) --ilosc energii po odbiciu (odbijanie sie od obiektu)
		EntitySetMaterialStaticFriction(name, 0.5) --sila miedzy obiektami statycznymi
		EntitySetMaterialDynamicFriction(name, 0.5) --sila miedzy obiektami dynamicznymi
		EntityRaiseBodyFlag(name, BodyFlag.kinematic)
		--ewentualne callbacki
	else
		ShowError("Nie mozna stworzyc StoneBall: " .. name)
		return false
	end
end
]]--