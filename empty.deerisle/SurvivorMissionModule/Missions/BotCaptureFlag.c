class CaptureFlagMission extends SurvivorMissions
{		
	//Mission related entities 
	ItemBase MissionObject;
	Object FlagBase, Table1, Table2;
	BarrelHoles_ColorBase BarrelFire;
	Flag_Base Flag;
		
	//Mission parameters
	int MsgDlyFinish = 60;					//seconds, message delay time after player has finished mission
	int HordeDensity = 60;					//infected, spawned in circle area
	int CaptureTime = 1200;					//seconds, time to capture the flag ..full minutes (60,120,...)
	string DownFlag = "Flag_Bohemia";		//class name of flag to lower
	string UpFlag = "Flag_Chernarus";		//class name of flag to raise
	
	//mission vars
	vector PoleHighPos, PoleLowPos;		
	float flag_speed, delta_height;
	int FlagElevationChkTime;
	int FireplaceSpendChkTime;
	int FlagCaptureProgress;
	int TeamPlayerCount;
	bool CaptureFinished = false;
	
	//Mission containers
	ref array<ref Param3<string,vector,vector>> BuildingSpawns = new array<ref Param3<string,vector,vector>>;
	ref array<vector> Spawnpoints = new array<vector>;
	ref array<vector> FireSpawns = new array<vector>;
	ref array<vector> InfectedSpawns = new array<vector>;
	ref array<string> InfectedTypes = new array<string>;
	ref array<vector> patrol_101 = {"-50 0 50","-40 0 40","-20 0 -0","-10 0 10","-5 0 5","-2 0 2"};
	eAIGroup deletethis = null
	
	bool IsExtended() return true;
	
	void CaptureFlagMission()
	{
		//Select primary mission
		m_MissionExtended = true;
		
		//Mission mission timeout
		m_MissionTimeout = 2700;			//seconds, mission duration time
		
		//Mission zones
		m_MissionZoneOuterRadius = 700.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 100.0;	//meters (!Do not set outside of base radius), mission finishing distance to target object
		
		//Mission informant
		m_MissionInformant = "Dr. Legasov";
		
		//Translate mission location name and direction
/*
		if ( MissionSettings.Opt_TranslateEWData )
		{
			m_MissionLocation = EventsWorldData.TransLoc( m_MissionLocation );
			m_MissionLocationDir = EventsWorldData.TransDir( m_MissionLocationDir );
		}
*/				
		//Set mission messages
		m_MissionMessage1 = "One of our defense positions was occupied by the Bohemian Bandits yesterday. Because of the exchange of fire between the bandits and a few survivor's alot of infected were attracted.";
		m_MissionMessage2 = "Find the defense position and capture the base flag for us. It needs atleast "+ ( CaptureTime / 60 ).ToString() +" minutes to lower the bandit's flag and raise our own.";
		m_MissionMessage3 = "The defense position is at the ** "+ m_MissionLocationDir +" side of "+ m_MissionLocation +" **\nBe careful, there are alot of infected and the bandits might be still around there!";
		
		//Rewards spawns
		Spawnpoints.Insert("-0.422 0.453 0");	//table 1
		Spawnpoints.Insert("0.486 0.453 0");	//table 1
		Spawnpoints.Insert("0 0.453 0");		//table 2
		
		//Fireplace spawns
		FireSpawns.Insert("0 0 10");
		FireSpawns.Insert("0 0 -10");

				//Infected spawnpoints
		InfectedSpawns.Insert("-10.5186 0 25.0269");
		InfectedSpawns.Insert("24.9775 0 -10.4146");
		InfectedSpawns.Insert("-30.1726 0 -6.2729");
		InfectedSpawns.Insert("-20.9209 0 4.6636");
		InfectedSpawns.Insert("15.0283 0 -10.3276");
		InfectedSpawns.Insert("7.2461 0 30.5884");
		InfectedSpawns.Insert("-20.6855 0 5.9956");
		
		//Infected types
		//Male												//Female
		InfectedTypes.Insert("ZmbM_CitizenASkinny_Brown");	InfectedTypes.Insert("ZmbF_JournalistNormal_White");
		InfectedTypes.Insert("ZmbM_priestPopSkinny");		InfectedTypes.Insert("ZmbF_Clerk_Normal_White");
		InfectedTypes.Insert("ZmbM_HermitSkinny_Beige");	InfectedTypes.Insert("ZmbF_CitizenANormal_Blue");
		InfectedTypes.Insert("ZmbM_CitizenBFat_Red");		InfectedTypes.Insert("ZmbF_CitizenBSkinny");
		InfectedTypes.Insert("ZmbM_FishermanOld_Green");	InfectedTypes.Insert("ZmbF_HikerSkinny_Grey");
		InfectedTypes.Insert("ZmbM_HunterOld_Autumn");		InfectedTypes.Insert("ZmbF_SurvivorNormal_Orange");
		InfectedTypes.Insert("ZmbM_CitizenBFat_Blue");		InfectedTypes.Insert("ZmbF_HikerSkinny_Green");
		InfectedTypes.Insert("ZmbM_MotobikerFat_Black");	InfectedTypes.Insert("ZmbF_JoggerSkinny_Green");
		InfectedTypes.Insert("ZmbM_JoggerSkinny_Red");		InfectedTypes.Insert("ZmbF_SkaterYoung_Striped");
		InfectedTypes.Insert("ZmbM_MechanicSkinny_Grey");	InfectedTypes.Insert("ZmbF_BlueCollarFat_Red");
		InfectedTypes.Insert("ZmbM_HandymanNormal_Green");	InfectedTypes.Insert("ZmbF_MechanicNormal_Beige");
		InfectedTypes.Insert("ZmbM_HeavyIndustryWorker");	InfectedTypes.Insert("ZmbF_PatientOld");
		InfectedTypes.Insert("ZmbM_Jacket_black");			InfectedTypes.Insert("ZmbF_ShortSkirt_beige");
		InfectedTypes.Insert("ZmbM_Jacket_stripes");		InfectedTypes.Insert("ZmbF_VillagerOld_Red");
		InfectedTypes.Insert("ZmbM_HikerSkinny_Blue");		InfectedTypes.Insert("ZmbF_JoggerSkinny_Red");
		InfectedTypes.Insert("ZmbM_HikerSkinny_Yellow");	InfectedTypes.Insert("ZmbF_MilkMaidOld_Beige");
		InfectedTypes.Insert("ZmbM_PolicemanFat");			InfectedTypes.Insert("ZmbF_VillagerOld_Green");
		InfectedTypes.Insert("ZmbM_PatrolNormal_Summer");	InfectedTypes.Insert("ZmbF_ShortSkirt_yellow");
		InfectedTypes.Insert("ZmbM_JoggerSkinny_Blue");		InfectedTypes.Insert("ZmbF_NurseFat");
		InfectedTypes.Insert("ZmbM_VillagerOld_White");		InfectedTypes.Insert("ZmbF_PoliceWomanNormal");
		InfectedTypes.Insert("ZmbM_SkaterYoung_Brown");		InfectedTypes.Insert("ZmbF_HikerSkinny_Blue");
		InfectedTypes.Insert("ZmbM_MechanicSkinny_Green");	InfectedTypes.Insert("ZmbF_ParamedicNormal_Green");
		InfectedTypes.Insert("ZmbM_DoctorFat");				InfectedTypes.Insert("ZmbF_JournalistNormal_Red");
		InfectedTypes.Insert("ZmbM_PatientSkinny");			InfectedTypes.Insert("ZmbF_SurvivorNormal_White");
		InfectedTypes.Insert("ZmbM_ClerkFat_Brown");		InfectedTypes.Insert("ZmbF_JoggerSkinny_Brown");
		InfectedTypes.Insert("ZmbM_ClerkFat_White");		InfectedTypes.Insert("ZmbF_MechanicNormal_Grey");
		InfectedTypes.Insert("ZmbM_Jacket_magenta");		InfectedTypes.Insert("ZmbF_BlueCollarFat_Green");
		InfectedTypes.Insert("ZmbM_PolicemanSpecForce");	InfectedTypes.Insert("ZmbF_DoctorSkinny");

		//Spawn surrounding flag base buildings
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Roadblock_WoodenCrate", "-1.5 0 4", "65 0 90"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Roadblock_WoodenCrate", "1.5 0 4", "135 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Roadblock_Table", "-1.5 0 -3", "15 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Roadblock_Table", "1.5 0 -3", "0 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("BarrelHoles_Blue", "1.8 0 1.8", "0 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Mil_Fortified_Nest_Watchtower", "9 0 9", "135 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Mil_Fortified_Nest_Watchtower", "-9 0 -9", "315 0 0"));		
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Wreck_Ikarus", "13 0 -2.8", "-160 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_Wreck_Uaz", "-12 0 2.8", "15 0 0"));
		BuildingSpawns.Insert( new Param3<string,vector,vector>("Land_wreck_truck01_aban1_orange", "0 0 13.5", "90 0 0"));
		
		//Clean up flag base position		
		GetGame().GetObjectsAtPosition( m_MissionPosition, 18.0 , m_ObjectList, m_ObjectCargoList );
		for ( int b=0; b < m_ObjectList.Count(); b++) 
		{
			Object FoundObject = m_ObjectList.Get(b);
			if ( FoundObject.IsItemBase() )
			{
				Print("[SMM] BeforeSpawnCleanUp :: Object deleted: "+ FoundObject );  
				GetGame().ObjectDelete( FoundObject );
			}
		}
		
		//Activate EntityChecks
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( EntityChecks, 0, true );
	}
	
	void ~CaptureFlagMission()
	{		
		//Despawn all remaining mission objects
		if ( m_MissionObjects )
		{	
			Print("[SMM] Despawning "+ m_MissionObjects.Count() +" mission objects from old mission...");				
			for ( int i = 0; i < m_MissionObjects.Count(); i++ )
			{ 
				if ( !m_MissionObjects.Get(i) ) continue;
				else
				{
					//Delete Object serverside
					GetGame().ObjectDelete( m_MissionObjects.Get(i) );
				}		
			}
			m_MissionObjects.Clear();
		}
		
		//Despawn mission AI's
		#ifdef EAI
		if ( m_MissionAIs )
		{
			if ( m_MissionAIs.Count() > 0 )
			{
				Print("[SMM] Despawning "+ m_MissionAIs.Count() +" mission AI's from old mission...");
				for ( int k = 0; k < m_MissionAIs.Count(); k++ )
				{
					
					GetGame().ObjectDelete( m_MissionAIs.Get(k) );
				}
				m_MissionAIs.Clear();			
			}
			else Print("[SMM] No mission AI's to despawn.");
		}
		eAIGroup g = deletethis;
				for (int r = g.Count() - 1; r > -1; r--) {
					PlayerBase p = g.GetMember(r);
					if (p.IsAI()) {
						g.RemoveMember(r);
						GetGame().ObjectDelete(p);
					}
				}	
		#endif
		//Delete PlayersInZone list & reset container takeaway
		if ( m_PlayersInZone )	m_PlayersInZone.Clear();
		if ( m_ContainerWasTaken ) m_ContainerWasTaken = false;	
	}	
	
	void SpawnObjects()
	{		
		//spawn flagpole (flagpole is the reference for all mission building & object spawnpoints!) 
		FlagBase = GetGame().CreateObject( "Land_Power_Pole_Conc4_Lamp_Amp", m_MissionPosition );
		FlagBase.SetPosition( m_MissionPosition + "0 4 0" );
		FlagBase.SetOrientation( Vector( Math.RandomFloatInclusive(0,359.9), 0 , 0));
		m_MissionObjects.Insert( FlagBase );											//Object 0

		//get flag height limits and offset height positions min max
		vector temp = FlagBase.ModelToWorld("0.82 0 -0.18");
		temp[1] = GetGame().SurfaceY(temp[0], temp[2]);
		PoleHighPos = temp + "0 9.47 0";
		PoleLowPos = temp + "0 3 0";
		
		//flag hight and speed calculations
		delta_height = PoleHighPos[1] - PoleLowPos[1];						//height diff min max ...[m]
		flag_speed = -( delta_height / (( CaptureTime / 2 ) * 10 ) );		//vertical speed of flag movement, v = s / t ...[m/100ms]
		
		//spawn flag
		Flag = Flag_Base.Cast( GetGame().CreateObject( DownFlag, PoleHighPos ));
		Flag.SetPosition( PoleHighPos );
		Flag.SetOrientation( FlagBase.GetOrientation() + "0 0 0");
		Flag.ShowSelection("unfolded");
		Flag.HideSelection("folded");
		Flag.SetTakeable(false);
		Flag.SetLifetime(7200);
		m_MissionObjects.Insert( Flag );												//Object 1
		
		//Spawn additional flag base buildings and objects
		for ( int i=0; i < BuildingSpawns.Count(); i++ )
		{
			Param3<string,vector,vector> BuildingDef = BuildingSpawns.Get(i);
			string BuildingType = BuildingDef.param1;
			vector BuildingPos = FlagBase.ModelToWorld( BuildingDef.param2 );
			vector BuildingOri = BuildingDef.param3;
			vector BuildingDir = FlagBase.GetDirection();
			
			BuildingPos[1] = GetGame().SurfaceY( BuildingPos[0], BuildingPos[2] );
			Object HQextra = GetGame().CreateObject( BuildingType, BuildingPos );
			HQextra.SetDirection( BuildingDir );
			HQextra.SetOrientation( HQextra.GetOrientation() + BuildingOri );
			HQextra.PlaceOnSurface();
			m_MissionObjects.Insert( HQextra );											//Object 2 to 8
		}
		
		//check darkness for location light support and spawn fireplaces
		int year, month, day, hour, minute;
		
		GetGame().GetWorld().GetDate( year, month, day, hour, minute );		
		
		Mission currentMission = GetGame().GetMission();

		if ( currentMission )
		{			
			WorldData worldData = currentMission.GetWorldData();
			if ( worldData )
			{
				float ApproxSunrise = worldData.GetApproxSunriseTime( month + ( day / 32.0 ) );
				float ApproxSunset = worldData.GetApproxSunsetTime( month + ( day / 32.0 ) );
				
				int SunRiseHour = Math.Round( ApproxSunrise + 0.25 );
				int SunSetHour = Math.Round( ApproxSunset - 0.25 );
				
				if ( MissionSettings.DebugMode )
				Print("[SMM] Test Hour is "+ hour +", SunRiseHour: "+ SunRiseHour +", SonSetHour: "+ SunSetHour );
				
				if ( hour >= SunSetHour || hour <= SunRiseHour ) 
				{
					EntityAI wood, stones;
					
					for ( int k=0; k < FireSpawns.Count(); k++)
					{
						vector CampfirePosition = FlagBase.ModelToWorld( FireSpawns.Get(k) );
						
						//fireplace
						FireplaceBase Campfire = FireplaceBase.Cast( GetGame().CreateObject( "Fireplace", CampfirePosition ) );
						Campfire.Synchronize();
						wood = Campfire.GetInventory().CreateAttachment("Firewood");
						ItemBase.Cast( wood ).SetQuantity(6);
						Campfire.GetInventory().CreateAttachment("WoodenStick");
						Campfire.GetInventory().CreateAttachment("Rag");
						stones = Campfire.GetInventory().CreateAttachment("Stone");
						ItemBase.Cast( stones ).SetQuantity(16);
						Campfire.StartFire( true );
						m_MissionObjects.Insert( Campfire );
						
						//Cluttercutter fireplace
						Object cc_fireplace = GetGame().CreateObject( "ClutterCutterFireplace" , Campfire.GetPosition() );
						cc_fireplace.SetOrientation( Campfire.GetOrientation() );
						GetGame().RemoteObjectCreate( cc_fireplace );
						m_MissionObjects.Insert( cc_fireplace );
					}
				}
			}
		}
		
		//flip flagpole after spawning all objects
		FlagBase.SetOrientation( FlagBase.GetOrientation() + "0 180 0");
		
		Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
	}
	
	void SpawnRewards()
	{
		Table1 = m_MissionObjects[4];
		Table2 = m_MissionObjects[5];
		
		for (int i=0; i < TeamPlayerCount; i++)
		{
			vector spawnpos;
			
			if ( i < 2 )
			spawnpos = Table1.ModelToWorld( Spawnpoints.Get(i) );
			else spawnpos = Table2.ModelToWorld( Spawnpoints.Get(i) );
			
			//Mission object is seachest
			MissionObject = ItemBase.Cast( GetGame().CreateObject("SeaChest", spawnpos) ); 
			
			//Get random loadout 			
			int selectedLoadout = Math.RandomIntInclusive(0,9);	//!Change randomization limit after adding new loadouts!
			
			//Spawn selected loadout items in mission object
			EntityAI weapon;
									
			if (selectedLoadout == 0)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_HK416Black");
				weapon.GetInventory().CreateAttachment("M4_OEBttstck");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("BakedBeansCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
		}
		if (selectedLoadout == 1)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_Beowulf");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
			MissionObject.GetInventory().CreateInInventory("TTC_50Beo_mag");
			MissionObject.GetInventory().CreateInInventory("TTC_50Beo_mag");
			MissionObject.GetInventory().CreateInInventory("TTC_AmmoBox_50Beo_20rnd");
			MissionObject.GetInventory().CreateInInventory("TTC_AmmoBox_50Beo_20rnd");
			MissionObject.GetInventory().CreateInInventory("CanOpener");
			MissionObject.GetInventory().CreateInInventory("PeachesCan");
			MissionObject.GetInventory().CreateInInventory("WaterBottle"); 
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
		}
		if (selectedLoadout == 2)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_AACHoney_300blk");
				weapon.GetInventory().CreateAttachment("TTC_Buttstock_Honey");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
				weapon.GetInventory().CreateAttachment("TTC_Honey_Suppressor");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("KitchenKnife");
			MissionObject.GetInventory().CreateInInventory("SardinesCan");
			MissionObject.GetInventory().CreateInInventory("Canteen");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackBlackFrost");
		}
		if (selectedLoadout == 3)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_M4Tac");
				weapon.GetInventory().CreateAttachment("TTC_Buttstock_Morty");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("MilitaryBelt");	
			MissionObject.GetInventory().CreateInInventory("M18SmokeGrenade_Yellow");	
			MissionObject.GetInventory().CreateInInventory("TacticalBaconCan");
			MissionObject.GetInventory().CreateInInventory("SteakKnife");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackBlackFrost");
		}	
		if (selectedLoadout == 4)
		{
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_M16A4");
				weapon.GetInventory().CreateAttachment("ACOGOptic");
				weapon.GetInventory().CreateAttachment("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			MissionObject.GetInventory().CreateInInventory("Ammo_556x45");
			weapon = MissionObject.GetInventory().CreateInInventory("FNX45");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
				weapon.GetInventory().CreateAttachment("TLRLight");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");			
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackBlackFrost");
			MissionObject.GetInventory().CreateInInventory("CJ_Keycard_11SR");
		}
		if (selectedLoadout == 5)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_M14");
				weapon.GetInventory().CreateAttachment("HuntingOptic");		
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");
			MissionObject.GetInventory().CreateInInventory("Ammo_308Win");		
			weapon = MissionObject.GetInventory().CreateInInventory("FNX45");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");
				weapon.GetInventory().CreateAttachment("FNP45_MRDSOptic");
				weapon.GetInventory().CreateAttachment("TLRLight");
			MissionObject.GetInventory().CreateInInventory("Mag_FNX45_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Ammo_45ACP");					
			weapon = MissionObject.GetInventory().CreateInInventory("NVGHeadstrap");
				weapon.GetInventory().CreateInInventory("NVGoggles");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("TTC_M14_Mag_20rnd");
			MissionObject.GetInventory().CreateInInventory("TTC_M14_Mag_20rnd");
			MissionObject.GetInventory().CreateInInventory("Bear_Pink");
			MissionObject.GetInventory().CreateInInventory("M67Grenade");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");				
		}
		if (selectedLoadout == 6)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_MP7A1");
				weapon.GetInventory().CreateAttachment("TTC_Holo");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");			
			MissionObject.GetInventory().CreateInInventory("TTC_MP7A1_Mag_40rnd");
			MissionObject.GetInventory().CreateInInventory("TTC_MP7A1_Mag_40rnd");
			MissionObject.GetInventory().CreateInInventory("TTC_Ammo_4630");
			MissionObject.GetInventory().CreateInInventory("TTC_Ammo_4630");
			MissionObject.GetInventory().CreateInInventory("TTC_Ammo_4630");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");	
			MissionObject.GetInventory().CreateInInventory("TunaCan");
			MissionObject.GetInventory().CreateInInventory("RDG5Grenade");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackNomad");				
		}	
		if (selectedLoadout == 7)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_AWM");
				weapon.GetInventory().CreateAttachment("HuntingOptic");		
			MissionObject.GetInventory().CreateInInventory("TTC_AWM_Magazine_5rnd");
			MissionObject.GetInventory().CreateInInventory("TTC_AWM_Magazine_5rnd");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackNomad");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");				
		}
		if (selectedLoadout == 8)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_MCX_Spear_Black");
				weapon.GetInventory().CreateAttachment("TTC_Elcan");
				weapon.GetInventory().CreateAttachment("TTC_MPXMCXSPEAR_Bttstck");
				weapon.GetInventory().CreateAttachment("TTC_MCX_Spear_Suppressor");	
			MissionObject.GetInventory().CreateInInventory("TTC_MCX_Spear_Magazine_20rnd");
			MissionObject.GetInventory().CreateInInventory("TTC_MCX_Spear_Magazine_20rnd");
			MissionObject.GetInventory().CreateInInventory("WaterBottle");	
			MissionObject.GetInventory().CreateInInventory("SpaghettiCan");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackS1");
			MissionObject.GetInventory().CreateInInventory("CP_CigarettePack_CannabisS1");				
		}
		if (selectedLoadout == 9)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_MK18");
				weapon.GetInventory().CreateAttachment("TTC_Elcan");
				weapon.GetInventory().CreateAttachment("M4_OEBttstck");				
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_STANAG_30Rnd");
			MissionObject.GetInventory().CreateInInventory("Canteen");	
			MissionObject.GetInventory().CreateInInventory("TacticalBaconCan");
			MissionObject.GetInventory().CreateInInventory("Tomato");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");				
		}
		
			//barrel add firewood and start fire
			BarrelFire = BarrelHoles_ColorBase.Cast( m_MissionObjects[6] );
			BarrelFire.Open();
			BarrelFire.Synchronize();
			
			EntityAI barrel_wood = BarrelFire.GetInventory().CreateAttachment("Firewood"); 		
			BarrelFire.GetInventory().CreateAttachment("WoodenStick");
			BarrelFire.GetInventory().CreateAttachment("Rag");
			BarrelFire.StartFire( true );
			ItemBase.Cast( barrel_wood ).SetQuantity(6);
			
			//spawn 5 fish filets for smoking in barrel
			if ( BarrelFire.IsOpen() )	BarrelFire.Close();
			for ( i=0; i < 7; i++)
			BarrelFire.GetInventory().CreateAttachment("MackerelFilletMeat");

			Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+ selectedLoadout +"." );
		}
		
		//log team work players
		for ( i=0; i < m_PlayersInZone.Count(); i++)
		Print("[SMM] Player with SteamID64: "+ m_PlayersInZone.Get(i) +" has assisted capturing the flag.");
	}
	#ifdef EAI

	eAIGroup m_activeGroup = null;

	void SpawnPatrol(vector pos, string loadout = "Army.json") 
	{
    	eAIGame game = MissionServer.Cast(GetGame().GetMission()).GetEAIGame();
		eAIBase ai = game.SpawnAI_Patrol(pos, loadout);
	
		//	m_MissionAIs.Insert(ai);
		m_activeGroup = ai.GetGroup();

		deletethis = ai.GetGroup();

		foreach (int i, vector v : patrol_101) 
		{
			m_activeGroup.AddWaypoint(v);
		}


		int count = 3; // temporary so we don't decrease the actual amount

		while (count > 1) 
		
		{
			(game.SpawnAI_Helper(ai, loadout)).RequestTransition("Rejoin");
			//m_MissionAIs.Insert(ai);
			count--;
		}
	}
	
	#endif
	void SpawnStuff()
	{
		//Bot Patrol	
		for (int u = 0; u < patrol_101.Count(); u++) 
		{
			vector pos = m_MissionPosition + patrol_101[u];
			float x = pos[0] + Math.RandomFloat(-12, 12);
			float z = pos[2] + Math.RandomFloat(-12, 12);
			float y = GetGame().SurfaceY(x, z);
			patrol_101[u] = Vector (x, y, z);
		}
		vector gpos = { Math.RandomFloatInclusive(-50, -30.0), 0, Math.RandomFloatInclusive(-50.0, -30.0) };
		vector SoldierBotPos1 = FlagBase.ModelToWorld(gpos);
		SpawnPatrol(SoldierBotPos1);	
	}

	#ifdef EAI

	#endif
	void SpawnAIs()
	{	
		//Spawn infected
		for ( int z = 0 ; z < InfectedSpawns.Count() ; z++ )
		{
			string RandomInfected = InfectedTypes.GetRandomElement();
			vector InfectedPos = FlagBase.ModelToWorld( InfectedSpawns.Get(z) );
			m_MissionAIs.Insert( GetGame().CreateObject( RandomInfected, InfectedPos, false, true ) );
		}		

		//Spawn infected time delayed 1,500,000ms = 25 min delay
		int BotDlyTime = 1500000;
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( SpawnStuff, BotDlyTime, false );
			
		//  Spawn horde on Timer
		for ( int j = 0; j < HordeDensity; j++ )
		{
			//Spawn infected time delayed 480000ms = 8 min delay
			int InfectedDlyTime = 480000;
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( DelayedAISpawn, InfectedDlyTime, false );
			InfectedDlyTime += 480000;
		}	

	}


	void DelayedAISpawn()
	{
		//calc new spawn position
		float x = Math.RandomFloatInclusive( 20 , 50 );
		float y = Math.RandomFloatInclusive( 20 , 50 );	
		int Dice = Math.RandomIntInclusive( 0, 9);
		if ( Dice > 4 ) x *= -1.0;
		Dice = Math.RandomIntInclusive( 0, 9);
		if ( Dice < 5 ) y *= -1.0;
		vector NewPosVector = { x, 0, y };
		
		//spawn infected
		m_MissionAIs.Insert( GetGame().CreateObject( InfectedTypes.GetRandomElement(), m_MissionPosition + NewPosVector, false, true ));
	
	}
	void ObjDespawn() 
	{	
		//nothing to despawn
	}
	
	void ExtendMission()
	{
		//select secondary mission
		m_MissionExtended = false;
		
		//Set new mission messages
		m_MissionMessage1 = "Allright survivor, it seems you have found the defence position "+ m_MissionLocationDir +" of "+ m_MissionLocation +". There are probably alot of infected, try to get in there safely and hold the position.";
		m_MissionMessage2 = "Be aware, Bohemian Bandits could counter attack the defence position. If you could capture it completely, there will be some interesting equipment for you probably.";
		m_MissionMessage3 = "The flag was already captured by "+ FlagCaptureProgress +"%. Hold on, you will make it.";
		
		//init Messenger for new messages
		m_MsgNum = 1;					//skip msg 0, begin with msg 1
		m_MsgChkTime = m_MissionTime;
		MsgCutoff = false;
		
		//increase mission MissionTimeout
		m_MissionTimeout = m_MissionTime + CaptureTime + 900;  
		
		//deployment settings & init for extended mission
		m_MissionZoneOuterRadius = 20.0;
		m_MissionZoneInnerRadius = 0.0001;
	}
			
	void MissionFinal()
	{	//When player enters last mission target zone	

		//Finish mission
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = m_MissionTime + MsgDlyFinish;			
	}
	
	void PlayerChecks( PlayerBase player )
	{	//Executed continuously only on players in the mission zone. Avoid complex calculations or big data processing!
		//nothing to check related to player
	}
	
	void EntityChecks()
	{	//Executed continuously while mission is active and triggered. Avoid complex calculations or big data processing!
		int crntTime = GetGame().GetTime();
		
		//flag movement & capture progress calculation
		if ( !m_MissionExtended && !CaptureFinished && FlagBase && Flag && m_PlayersInZone.Count() > 0 )
		{			
			if ( !FlagElevationChkTime ) FlagElevationChkTime = crntTime;
			
			if ( crntTime >= FlagElevationChkTime + 100 )	//checking every 100ms
			{
				vector FlagPos = Flag.GetPosition();
				vector OldFlagPos;
				vector OldFlagOri;
				float flag_height = FlagPos[1];
			
				//check if flag is at lowest position
				if ( flag_height < PoleLowPos[1] && flag_speed < 0 ) 
				{
					flag_speed *= -1;
					
					//replace flag
					OldFlagPos = FlagPos;
					OldFlagOri = Flag.GetOrientation();
					
					GetGame().ObjectDelete( Flag );
					
					Flag = Flag_Base.Cast( GetGame().CreateObject( UpFlag, OldFlagPos ));
					Flag.SetPosition( OldFlagPos );
					Flag.SetOrientation( OldFlagOri );
					Flag.ShowSelection("unfolded");
					Flag.HideSelection("folded");
					Flag.SetTakeable(false);					
				}
				
				//check if flag is at highest position
				if ( flag_height > PoleHighPos[1] && flag_speed > 0 ) 
				{
					flag_speed *= -1;
					
					//check if flag has desired type
					if ( Flag.GetType() == UpFlag )
					{
						CaptureFinished = true;
						
						TeamPlayerCount = m_PlayersInZone.Count();
						if ( TeamPlayerCount > 3 ) TeamPlayerCount = 3;
						
						//spawn rewards & finish mission
						SpawnRewards();
						MissionFinal();
						
						//Deactivate EntityChecks
						GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove( EntityChecks );
					}
				}
				
				//update flag position
				Flag.SetPosition( FlagPos + Vector(0,flag_speed,0) );
				
				FlagElevationChkTime = crntTime;
			}

			//flag capture progress 0-100% (only for the progress in the message)
			if ( FlagPos[1] - PoleLowPos[1] > 0 && FlagPos[1] - PoleHighPos[1] < 0 )
			{
				if ( flag_speed < 0 ) 	//when lowering flag
				FlagCaptureProgress = 50 + ( FlagPos[1] - PoleLowPos[1] ) / ( -delta_height * 2 / 100 ); 
				else					//when raising flag
				FlagCaptureProgress = 50 + ( FlagPos[1] - PoleLowPos[1] ) / ( delta_height * 2 / 100 );
			}
			
			//refresh message 3 (capture progress)
			if ( !m_MissionExtended )
			m_MissionMessage3 = "The flag was already captured by "+ FlagCaptureProgress +"%. Hold the position, you will make it.";
		}
		
		//refuel fireplaces (!does only work when fireplaces are element 2 and 4 in m_MissionObjects array!)
		if ( !CaptureFinished )
		{
			if ( !FireplaceSpendChkTime ) FireplaceSpendChkTime = crntTime;
			
			if ( crntTime >= FireplaceSpendChkTime + 300000 )	//checking every 5min
			{
				for ( int i=0; i < m_MissionObjects.Count(); i++)
				{
					Object AnyObject = m_MissionObjects.Get(i);
					
					if ( AnyObject && AnyObject.IsFireplace() )  //Inherited( FireplaceBase ) )
					{
						FireplaceBase Campfire = FireplaceBase.Cast( AnyObject ); //m_MissionObjects.[i * 2 + 2] ); 
						if ( Campfire )
						{
							for (int j=0; j < Campfire.GetInventory().AttachmentCount(); ++j )
							{
								ItemBase attachment = ItemBase.Cast( Campfire.GetInventory().GetAttachmentFromIndex(j) );
								if ( attachment && attachment.GetType() == "Firewood" )
								{
									if ( attachment.GetQuantity() < 4 )		attachment.SetQuantity(6);
								}
								
								//to delete
								Print("[SMM] "+ AnyObject.GetType() +" Fireplace "+ attachment.GetType() +", quantity: "+ attachment.GetQuantity() );
							}												
						}
					}
				}
				
				FireplaceSpendChkTime = crntTime;
			}
		}
	}
				
	bool DeployMission()
	{	//When first player enters the mission zone (primary/secondary)
		if ( m_MissionPosition != "0 0 0" )
		{
			if ( m_MissionExtended )
			{	//only if primary is selected
				//Call spawners	
				GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnObjects );
				GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.SpawnAIs, 5000, false );
			}
			return true;
		}
		else 
		{
			Print("[SMM] ERROR : Mission position was rejected or doesn't exist. MissionPosition is NULL!");
			return false;
		}
	}
}

