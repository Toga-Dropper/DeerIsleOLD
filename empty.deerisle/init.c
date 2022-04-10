//#include "$CurrentDir:mpmissions/empty.deerisle/eAI/AI_init.c"   //to connect to your mp missions ai init.c folder

static void SpawnObject(string type, vector position, vector orientation)
{
    auto obj = GetGame().CreateObjectEx(type, position, ECE_SETUP | ECE_UPDATEPATHGRAPH | ECE_CREATEPHYSICS);
    obj.SetPosition(position);
    obj.SetOrientation(orientation);
    obj.SetOrientation(obj.GetOrientation());
    obj.SetFlags(EntityFlags.STATIC, false);
    obj.Update();
    obj.SetAffectPathgraph(true, false);
    if (obj.CanAffectPathgraph()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
}

void main()
{
	SpawnObject("MCK_KeyGrinder", "5967.20 14.7398 4974.77", "162.000 -0.000000 -0.000000");
	
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
//	Weather weather = g_Game.GetWeather();

//	weather.MissionWeather(false);    // false = use weather controller from Weather.c

//	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
//	weather.GetRain().Set( 0, 0, 1);
//	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
	//GetCEApi().ExportProxyData( "16000 0 16000", 20480 );  //Center of map, radius of how far to go out and find buildings.
	//EditorLoaderModule.ExportLootData = true;
	
	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 11, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
//	InitDynamicPatrols();	
}
class CustomMission: MissionServer
{
		void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}
	
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}	

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
			
		   player.GetInventory().CreateInInventory("BakedBeansCan_Opened");    // added items
		   player.GetInventory().CreateInInventory("SardinesCan");    // added items
		   player.GetInventory().CreateInInventory("BaseballBat");    // added items	
		   player.GetInventory().CreateInInventory("HumanSteakMeat");    // added items		
		   player.GetInventory().CreateInInventory("Magnum");    // added items	
		   player.GetInventory().CreateInInventory("Ammo_357");    // added items			   
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}