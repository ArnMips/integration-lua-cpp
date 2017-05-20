
Property[Obj.Lighthouse.ID] = function(obj)
	local property = { }
	property.objtype	= Obj.Lighthouse.ID
	property.color		= (getParam(obj, Obj.Lighthouse.Prm.COLOR) == 0xff0000 and 0xff0000 or 0x008000)
	property.caracter	= (getParam(obj, Obj.Lighthouse.Prm.BRIGHTNESS) > 100	and 'O' or 'X')
	return property
end

Property[Obj.Rock.ID] = function(obj)
	local property = {}
	property.objtype	= Obj.Rock.ID
	property.color		= (getParam(obj, Obj.Rock.Prm.ALTITUDE) > 1200000 and 0xffffff or 0xa52a2a)
	property.caracter	= (getParam(obj, Obj.Rock.Prm.IS_VOLCANO) == true and 'V' or '')
	return property
end
 
Property[Obj.Underwater_rock.ID] = function(obj)
	local property = { }
	property.objtype	= Obj.Underwater_rock.ID
	property.color		= (getParam(obj, Obj.Underwater_rock.Prm.DEPTH) < 5 and 0xff0000 or 0x808080)
	
	return property
end

Property[Obj.Coastline.ID] = function(obj)
	local property = { }
	property.objtype	= Obj.Coastline.ID
	property.color		= (getParam(obj, Obj.Coastline.Prm.LENGTH) == "sand" and 0xffff00 or 0x808080)
	property.caracter	= (getParam(obj, Obj.Coastline.Prm.TYPE_OF_BEACH)  > 2000 and '+' or '-')
	return property
end