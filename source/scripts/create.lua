meshArray = {}
soundArray = {}
textureArray = {}
function AddMesh(filename)
	if meshArray[filename] == nil then
		if ResourceAddMesh(filename, "media/models/" .. filename) then
			meshArray[filename] = "media/models/" .. filename
			return true
		else
			return false
		end
	end
	return true
end
function AddTexture(filename)
	if soundArray[filename] == nil then
		if ResourceAddTexture(filename, "media/textures/" .. filename) then
			soundArray[filename] = "media/textures/" .. filename
			return true
		else
			return false
		end
	end
	return true
end
function AddSound(filename)
	if soundArray[filename] == nil then
		if RSoundAddFile(filename, "media/sound/" .. filename) then
			soundArray[filename] = "media/sound/" .. filename
			return true
		else
			return false
		end
	end
	return true
end

--funkcja dodaje podstawowa wersje mesha, nalezy po tym uzupelnic wartosci physxowe
function CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ , scaleX, scaleY, scaleZ, shape, Type, normalMap)
	if AddMesh(mesh) == false then
		ShowError("Nie mozna dodac mesha: " .. mesh)
		return ""
	end
	if AddTexture(texture) == false then
		ShowError("Nie mozna dodac tekstury: " .. texture)
		return ""
	end
	if normalMap ~= "" then
		if AddTexture(normalMap) == false then
			ShowError("Nie mozna dodac normalMapy: " .. normalMap)
			return ""
		end
	end
	
	local name2 = EntityCreate(name, Type)
	if name2 ~= "" then 
		EntitySetStartPosition(name2, posX, posY, posZ)
		EntitySetStartRotation(name2, rotX, rotY, rotZ)
		EntitySetStartScale(name2, scaleX, scaleY, scaleZ)
		if Type ~= EntityType.noPhysx then
			EntitySetPhysxShape(name2, shape)
		end
		EntitySetTexture(name2, texture)
		if normalMap ~= "" then EntitySetNormalMap(name2, normalMap) end
		if EntitySetMesh(name2, mesh) then
			return name2
		else
			ShowError("LUA: Nie mozna zaladowac mesha do obiektu " .. name .. ": " .. mesh)
			return ""
		end
	end
	return ""
end
function CreatePlatform(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	--ShowInfo("Name: " .. name .. ", texture: " .. texture .. ", mesh: " .. mesh)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.triangle, EntityType.physx, "")
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.0) --ilosc energii po odbiciu (odbijanie sie od obiektu)
		EntitySetMaterialStaticFriction(name2, 0.5) --sila miedzy obiektami statycznymi
		EntitySetMaterialDynamicFriction(name2, 0.3) --sila miedzy obiektami dynamicznymi
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
	end
end
function CreateBox(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.triangle, EntityType.physx, "")--inne_nrm.jpg
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.0)
		EntitySetMaterialStaticFriction(name2, 0.5)
		EntitySetMaterialDynamicFriction(name2, 0.5)
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
	end
end
function CreatePorecz(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.triangle, EntityType.physx, "metal_nrm.jpg")
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.01)
		EntitySetMaterialStaticFriction(name2, 0.5)
		EntitySetMaterialDynamicFriction(name2, 0.3)
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
	end
end
function CreateTor(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.triangle, EntityType.physx, "")
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.1)
		EntitySetMaterialStaticFriction(name2, 0.4)
		EntitySetMaterialDynamicFriction(name2, 0.4)
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
	end
end
function CreatePlatformaZamiana(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	--ShowInfo("Name: " .. name .. ", texture: " .. texture .. ", mesh: " .. mesh)
	local normalMap = "kula_kamien_nrm.jpg";
	if texture == "kula_drewno.jpg" then normalMap = "kula_drewno_nrm.jpg" end
	if texture == "kula_papier.jpg" then normalMap = "kula_papier_nrm.jpg" end
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.triangle, EntityType.physx, normalMap)
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.0) --ilosc energii po odbiciu (odbijanie sie od obiektu)
		EntitySetMaterialStaticFriction(name2, 0.5) --sila miedzy obiektami statycznymi
		EntitySetMaterialDynamicFriction(name2, 0.5) --sila miedzy obiektami dynamicznymi
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
		EntitySetTrigger(name2, 0.95, 0.1, 0.95)
		--Trigger.onEnter
		EntitySetTriggerCallback(name2, "zmianaTypuKuliStart", Trigger.onEnter)
		--EntitySetCallback(name2, "zmianaTypuKuliStart", Callback.onStartTouch)
	end
end
function CreateSkrzynia(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.convex, EntityType.physx, "skrzynia_nrm.jpg")
	if name2 ~= "" then
		EntitySetActorMaxAngularVelocity(name2, 10.0) --predkosc katowa
		DodajSkrzynie(name2)
	end
end
function CreateKulaDrewno(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.sphere, EntityType.physx, "kula_drewno_nrm.jpg")
	if name2 ~= "" then
			EntitySetActorAngularDamping(name2, 1.0)
			EntitySetActorMaxAngularVelocity(name2, 10.0)
			EntitySetActorMass(name2, 20.0)
			EntitySetMaterialRestitution(name2, 0.1)
			EntitySetMaterialStaticFriction(name2, 0.9)
			EntitySetMaterialDynamicFriction(name2, 0.8)
	end
end
function CreateKulaKamien(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.sphere, EntityType.physx, "kula_kamien_nrm.jpg")
	if name2 ~= "" then
			EntitySetActorAngularDamping(name2, 1.0)
			EntitySetActorMaxAngularVelocity(name2, 10.0)
			EntitySetActorMass(name2, 50.0)
			EntitySetMaterialRestitution(name2, 0.0)
			EntitySetMaterialStaticFriction(name2, 0.9)
			EntitySetMaterialDynamicFriction(name2, 0.9)
	end
end
function CreateKulaPapier(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local nameRender = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, 0, EntityType.noPhysx, "")
	if nameRender ~= "" then
		local namePhysx = CreateEntity(name .. "PhysX", "kulapapierconvex.x", texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.convex, EntityType.physx, "")
		if namePhysx ~= "" then
			EntitySetActorAngularDamping(namePhysx, 1.0)
			EntitySetActorMaxAngularVelocity(namePhysx, 10.0)
			EntitySetActorMass(namePhysx, 10.0)
			EntitySetMaterialRestitution(namePhysx, 0.9)
			EntitySetMaterialStaticFriction(namePhysx, 0.5)
			EntitySetMaterialDynamicFriction(namePhysx, 1.5)
			EntitySetBindObject(namePhysx, nameRender)
		end
	end
end
function CreateGwiazda(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local nameRender = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, 0, EntityType.noPhysx, "")
	if nameRender ~= "" then
		math.randomseed( os.time() )
		local tmpX = math.random(0,1)
		if tmpX == 0 then 
			tmpX = -1 
		end
		EntitySetAnimation(nameRender, math.random(70,100) * tmpX, 0.0, 0.0)
		local namePhysx = CreateEntity(nameRender .. "PhysX", mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.sphere, EntityType.physx, "")
		if namePhysx ~= "" then
			EntitySetActorAngularDamping(namePhysx, 1.0)
			EntitySetActorMaxAngularVelocity(namePhysx, 10.0)
			EntitySetActorMass(namePhysx, 10.0)
			EntitySetMaterialRestitution(namePhysx, 0.9)
			EntitySetMaterialStaticFriction(namePhysx, 0.5)
			EntitySetMaterialDynamicFriction(namePhysx, 1.5)
			EntitySetBindObject(namePhysx, nameRender)
			EntityRaiseBodyFlag(namePhysx, BodyFlag.kinematic)
			EntitySetTrigger(namePhysx, 1.3, 1.3, 1.3)
			--Trigger.onEnter
			EntitySetTriggerCallback(namePhysx, "zebranieAurory", Trigger.onEnter)
		end
	end
end
function CreateSmiglo(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, 0, EntityType.noPhysx, "")
	DodajSmiglo(name2)
end
function CreateKrata(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.triangle, EntityType.physx, "metal_nrm.jpg")
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.0) --ilosc energii po odbiciu (odbijanie sie od obiektu)
		EntitySetMaterialStaticFriction(name2, 0.5) --sila miedzy obiektami statycznymi
		EntitySetMaterialDynamicFriction(name2, 0.3) --sila miedzy obiektami dynamicznymi
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
		DodajWentylator(name2)
	end
end
function CreateOtherStatic(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.box, EntityType.physx, "")
	if name2 ~= "" then
		EntitySetActorAngularDamping(name2, 1.0)
		EntitySetActorMaxAngularVelocity(name2, 10.0)
		EntitySetMaterialRestitution(name2, 0.1)
		EntitySetMaterialStaticFriction(name2, 0.5)
		EntitySetMaterialDynamicFriction(name2, 0.3)
		EntityRaiseBodyFlag(name2, BodyFlag.kinematic)
	end
end
function CreateOtherDynamic(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local name2 = CreateEntity(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, PhysxShape.box, EntityType.physx, "")
	if name2 ~= "" then
			EntitySetActorAngularDamping(name2, 1.0)
			EntitySetActorMaxAngularVelocity(name2, 10.0)
			EntitySetActorMass(name2, 20.0)
			EntitySetMaterialRestitution(name2, 0.0)
			EntitySetMaterialStaticFriction(name2, 0.9)
			EntitySetMaterialDynamicFriction(name2, 0.9)
	end
end
function IrrXmlParserCallback(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	local rotZ = rotZ * (-1) --zamiana na LH
	if mesh == "platformabok1.x" or mesh == "platformabok2.x" or mesh == "platformarog.x" or mesh == "platforma.x" then
		return CreatePlatform(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "box.x" or mesh == "boxskosduzy.x" or mesh == "boxskosmaly.x" or mesh == "boxskoswciecieduzy.x" or mesh == "boxskoswcieciemaly.x" or mesh == "boxwciecie.x" or mesh == "boxwcieciestart.x" or mesh == "podjazdplaski.x" or mesh == "podjazdstromy.x" then
		return CreateBox(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end

	if mesh == "porecz1.x" or mesh == "porecz2.x" or mesh == "poreczrog.x" then
		return CreatePorecz(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "tor.x" or mesh == "torswider.x" or mesh == "torzakretdlugi.x" or mesh == "torzakretkrotki.x" then
		return CreateTor(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "platformazmiana.x" then
		return CreatePlatformaZamiana(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "kuladrewno.x" then
		return CreateKulaDrewno(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "kulakamien.x" then
		return CreateKulaKamien(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "kulapapier.x" then
		return CreateKulaPapier(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "skrzynia.x" then
		return CreateSkrzynia(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "wiatrak.x" then
		return CreateSmiglo(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "krata.x" then
		return CreateKrata(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	if mesh == "gwiazda.x" then
		return CreateGwiazda(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	end
	--if mesh == "deska.x" then
	--return CreateOtherDynamic(name, mesh, texture, posX, posY, posZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ)
	--end
end
