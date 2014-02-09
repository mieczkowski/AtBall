-- SKRZYNIE
skrzynie = {}
function DodajSkrzynie(name)
	table.insert(skrzynie,name)
end
function UaktualnijSkrzynie()
	if AktualnaKula == KulaPapier then
		for i,skrzynia in ipairs(skrzynie) do 
			EntitySetActorAngularDamping(skrzynia, 9.0) -- z jaka intensywnoscia sila znika po nadaniu
			EntitySetActorMass(skrzynia, 32.0) --masa
			EntitySetMaterialRestitution(skrzynia, 0.3) --odbijanie sie obiektu
			EntitySetMaterialStaticFriction(skrzynia, 0.9) --tarcie statyczne
			EntitySetMaterialDynamicFriction(skrzynia, 0.6) --tarcie dynamiczne
		end
	elseif AktualnaKula == KulaDrewno then
		for i,skrzynia in ipairs(skrzynie) do 
			EntitySetActorAngularDamping(skrzynia, 9.0) -- z jaka intensywnoscia sila znika po nadaniu
			EntitySetActorMass(skrzynia, 16.0) --masa
			EntitySetMaterialRestitution(skrzynia, 0.3) --odbijanie sie obiektu
			EntitySetMaterialStaticFriction(skrzynia, 0.5) --tarcie statyczne
			EntitySetMaterialDynamicFriction(skrzynia, 0.4) --tarcie dynamiczne
		end
	else
		for i,skrzynia in ipairs(skrzynie) do 
			EntitySetActorAngularDamping(skrzynia, 10.0) -- z jaka intensywnoscia sila znika po nadaniu
			EntitySetActorMass(skrzynia, 2.0) --masa
			EntitySetMaterialRestitution(skrzynia, 0.3) --odbijanie sie obiektu
			EntitySetMaterialStaticFriction(skrzynia, 0.3) --tarcie statyczne
			EntitySetMaterialDynamicFriction(skrzynia, 0.1) --tarcie dynamiczne
		end
	end
end

