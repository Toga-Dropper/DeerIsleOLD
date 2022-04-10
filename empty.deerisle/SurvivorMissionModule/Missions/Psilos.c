class PsilosMission extends SurvivorMissions
{
	//Mission related entities
	ItemBase MissionObject;
	Object MissionBuilding;

	//Mission parameters
	int ReqShroomsCount = 10;				//pieces, requested mushroom amount
	int ExtendedTimout = 1800;				//seconds, mission duration time for extended mission
	int MsgDlyFinish = 60;					//seconds, message delay time after player has finished mission
	
	//Mission containers
	ref array<vector> ExtendedPosList = new array<vector>;
	ref array<vector> Spawnpoints = new array<vector>;
	ref array<vector> InfectedSpawns = new array<vector>;
	ref array<string> InfectedTypes = new array<string>;
	
	//Mission variables 
	string SurvivorName;		
	string SurvivorExtName;
	
	bool IsExtended() return true;
	
	void PsilosMission()
	{	
		//Select primary mission
		m_MissionExtended = true;
				
		//Mission timeout
		m_MissionTimeout = 2700;			//seconds, mission max duration time
		
		//Mission zones
		m_MissionZoneOuterRadius = 70.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 30.0;	//meters (!Do not set outside of 1-5m), mission finishing distance to target object
				
		//Mission informant
		m_MissionInformant = "Dr. Legasov";
	
		//Mission person names
		TStringArray SurvivorNames = {"Yuri", "Michail", "Boris", "Valeri", "Anatoli", "Ivan", "Alexej", "Dimitrij", "Sergej", "Nikolai"};
		SurvivorName = SurvivorNames.GetRandomElement();
		TStringArray SurvivorExtNames = {"Dr. Tamarova", "Dr. Lorzinski", "Dr. Blosmanova", "Dr. Haidenau", "Dr. Gabarin", "Dr. Sloskova", "Dr. Belzin", "Dr. Homyuk", "Dr. Trademzyuk", "Dr. Jankarova"};
		SurvivorExtName = SurvivorExtNames.GetRandomElement();
		
		//Set mission messages for primary mission
		m_MissionMessage1 = SurvivorName +", a survivor i met a few days ago told me that there are some places around here with numerous occurrencies of a special mushroom. It's classification name is 'Psilocybe semilanceata'.";
		m_MissionMessage2 = "At the moment i am experimenting with the psychoactive ingredient Psilocybin on infected wild animals. The animals show interesting behaviors after 30 minutes of the oral intake. I can't say much about it yet, but for my experiments I need more mushrooms.";
		m_MissionMessage3 = SurvivorName +" said that he found some of those anywhere\n** "+ m_MissionLocationDir +" of "+ m_MissionLocation +" **\nI need "+ ReqShroomsCount +" more pieces of it. The mushrooms are very small. I recommend using a mushroom encyclopedia for possible occurrencies!";
		
		//Spawnpoints for MissionObject for secondary mission
		Spawnpoints.Insert("-8.2598 -5.3138 -3.3914");
		Spawnpoints.Insert("-9.3223 -5.3234 1.1267");
		Spawnpoints.Insert("2.4033 -1.7478 -3.8455");
		Spawnpoints.Insert("-5.2329 -1.7252 -3.8408");
		Spawnpoints.Insert("-9.3237 -1.7233 0.9534");
		Spawnpoints.Insert("2.8477 -1.7252 2.5952");
		Spawnpoints.Insert("0.7725 -1.7252 2.4839");
				
		//Infected spawnpoints for secondary mission
		InfectedSpawns.Insert("-6.9097 -5.9196 -2.2151"); //policeman
		InfectedSpawns.Insert("-7.7876 -5.9899 1.9773"); //policeman
		InfectedSpawns.Insert("-7.8467 -2.4139 1.9091"); //policeman
		InfectedSpawns.Insert("0.7358 -2.4106 -2.3098"); //policeman
		InfectedSpawns.Insert("1.3223 -5.9844 -3.1926"); //prisoner
		InfectedSpawns.Insert("1.0986 -5.9846 -1.3384"); //prisoner
		//...outside MissionBuilding 
		InfectedSpawns.Insert("-8.12 0 -5.97");
		InfectedSpawns.Insert("-2.81 0 -5.8");
		InfectedSpawns.Insert("0.41 0 -5.8");
		InfectedSpawns.Insert("6.7 0 6.41");
		InfectedSpawns.Insert("6 0 -1.85");
		
		//Infected types
		//Male												//Female
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
	}
	
	void ~PsilosMission()
	{	
		//Despawn all remaining objects
		if ( m_MissionObjects )
		{	
			Print("[SMM] Despawning "+ m_MissionObjects.Count() +" mission objects from old mission...");		
			for ( int i = 0; i < m_MissionObjects.Count(); i++ )
			{
				if ( !m_MissionObjects.Get(i) ) continue;
				else GetGame().ObjectDelete( m_MissionObjects.Get(i) );		
			}
			m_MissionObjects.Clear();
		}
		
		//Delete mission AI's
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
		
		//Delete PlayersInZone list & reset container takeaway
		if ( m_PlayersInZone )	m_PlayersInZone.Clear();
		if ( m_ContainerWasTaken ) m_ContainerWasTaken = false;
	}
	
	void SpawnContainer()
	{
		MissionObject =  ItemBase.Cast( GetGame().CreateObject( "SmallProtectorCase", m_MissionPosition ));
		m_MissionObjects.InsertAt( MissionObject, 0); 		
	}
	
	void SpawnRewards()
	{
		//new MissionObject after deleting protector case
		MissionObject = ItemBase.Cast( GetGame().CreateObject( "MountainBag_Green", m_MissionPosition ));
		
		//Get random loadout 
		int selectedLoadout = Math.RandomIntInclusive( 0, 9);	//!change randomization limit after adding new loadouts!	

		//Spawn selected loadout items in mission object
		EntityAI weapon;
				
		if ( selectedLoadout == 0 )
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
					
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+ selectedLoadout +"." );	
	}
	
	void SpawnObjects()
	{			
		if ( m_MissionExtended )
		{	
			//Spawn mushroom occurence		
			float OccurenceDist = 30 * 0.707 ;
			int MushroomsCount = Math.RandomIntInclusive( 50, 150);
			vector SpawnPos;
			bool ItemsAtGround = false; 
		 
			MissionObject = ItemBase.Cast( GetGame().CreateObject( "PsilocybeMushroom", m_MissionPosition ));
			if ( MissionObject ) Print("[SMM] Mushrooms occurence spawned around @ "+ MissionObject.GetPosition());
			
			m_MissionObjects.Insert( MissionObject );
			for ( int j = 1; j < MushroomsCount; j++ )
			{
				//calc new spawn position
				float x = Math.RandomFloatInclusive( 0.5 , OccurenceDist );
				float y = Math.RandomFloatInclusive( 0.5 , OccurenceDist );	
				int Dice = Math.RandomIntInclusive( 0, 9);
				if ( Dice > 4 ) x *= -1.0;
				Dice = Math.RandomIntInclusive( 0, 9);
				if ( Dice < 5 ) y *= -1.0;
				vector NewPosVector = { x, 0, y };
				SpawnPos = m_MissionPosition + NewPosVector;
				
				//check for items at ground
				GetGame().GetObjectsAtPosition( SpawnPos , 1.0 , m_ObjectList , m_ObjectCargoList );
				for ( int i = 0; i < m_ObjectList.Count(); i++ )
				{ 
					Object FoundObject = m_ObjectList.Get(i);
					if ( FoundObject.IsItemBase() || FoundObject.IsTree() || FoundObject.IsRock() || FoundObject.IsBush() ) 
					{
						ItemsAtGround = true;
						break;
					}
				}
				if ( ItemsAtGround )
				{
					ItemsAtGround = false;
					j--;
					continue;
				} 
			
				//spawn mushroom
				m_MissionObjects.Insert( GetGame().CreateObject( "PsilocybeMushroom", SpawnPos ));	
			}
				
			Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
		}
		else
		{				
			if ( MissionBuilding )
			{
				//Cleanup position before spawning protector case
				GetGame().GetObjectsAtPosition( m_MissionPosition, 0.5, m_ObjectList, m_ObjectCargoList );
				for ( int k = 0; k < m_ObjectList.Count(); k++ )
				{
					FoundObject = m_ObjectList.Get(k);
					if ( FoundObject.IsItemBase() )
					GetGame().ObjectDelete( FoundObject );
				}
				
				//Spawn container
				GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.SpawnContainer, 1000 );
								
				Print("[SMM] Survivor Mission Extension "+ m_selectedMission +" :: "+ m_MissionName +" ...mission extended!");
			}
			else Print("[SMM] Extended MissionBuilding couldn't be found in "+ m_MissionDescription[3] +" ... Mission rejected!");
		}
	}
	
	void SpawnAIs()
	{	
		if ( m_MissionExtended )
		{
			//Spawn no AIs at primary mission
		}
		else
		{
			//Spawn infected
			string RandomInfected;
			vector InfectedPos;
			
			//Spawn some infected at Police Station
			for ( int k = 0 ; k < InfectedSpawns.Count() ; k++ )
			{
				if ( k == 0 )	RandomInfected = "ZmbM_PolicemanFat";
				else if ( k == 1 )	RandomInfected = "ZmbF_PoliceWomanNormal";
				else if ( k == 2 )	RandomInfected = "ZmbM_PolicemanSpecForce";
				else if ( k == 3 )	RandomInfected = "ZmbM_PolicemanFat";
	    	   	else RandomInfected = InfectedTypes.GetRandomElement();
				InfectedPos = MissionBuilding.ModelToWorld( InfectedSpawns.Get(k) );
				DayZInfected Zed = DayZInfected.Cast( GetGame().CreateObject( RandomInfected, InfectedPos, false, true ));
				m_MissionAIs.Insert( Zed );
			}
		}
	}
	
	void ObjDespawn() 
	{	
		//Despawn all mission objects at mission timeout except those retains until next mission
		for ( int i = 0; i < m_MissionObjects.Count(); i++ )
		{
			//Exception: Psilo's will remain
			if ( m_MissionObjects.Get(i) && m_MissionObjects.Get(i).GetType() == "PsilocybeMushroom" )	continue;

			//Delete Object
			GetGame().ObjectDelete( m_MissionObjects.Get(i) );
			m_MissionObjects.Remove(i);
		}
	}
	
	void ExtendMission()
	{
		//Set new mission messages
		m_MissionMessage1 = "Allright survivor, if you have found "+ ReqShroomsCount +" of these mushrooms bring them to the following place. Hold on a second...";
		m_MissionMessage2 = "Bring them to the ** "+ m_MissionDescription[3] +" Police Station **\n"+ SurvivorExtName +" said she could extract the active substance for me. She has left a small protector case on the desk in the office.";
		m_MissionMessage3 = "Put all you have found in there. Be carefull, there might be bandits around which could intercepted our little radio talk here. Good luck!";
		
		//init Messenger for new messages
		m_MsgNum = 1;					//skip msg 0, begin with msg 1
		m_MsgChkTime = m_MissionTime;
		MsgCutoff = false;
		
		//increase mission MissionTimeout
		m_MissionTimeout = m_MissionTime + ExtendedTimout;  
		
		//deployment settings & init for extended mission
		m_MissionZoneOuterRadius = 90.0;
		m_MissionZoneInnerRadius = 2.0;
		
		//Get building position from building type and location
		if ( EventsWorldData.GetBuildingsAtLoc("Land_Village_PoliceStation_Enoch", m_MissionDescription[3], ExtendedPosList ))
		{			
			//Get MissionPosition for MissionBuilding from secondary mission
			m_MissionPosition = ExtendedPosList.GetRandomElement();						
			
		}
		else Print("[SMM] Can't find MissionBuilding Village Police Station in "+ m_MissionDescription[3] +"!");
	}
	
	void MissionFinal()
	{	//When player enters last mission target zone
		//do nothing			
	}
	
	void PlayerChecks( PlayerBase player )
	{
		//Check if container gets taken from player
		if ( MissionSettings.Opt_DenyObjTakeaway && !m_MissionExtended )
		{
			if ( m_MissionObjects[0] && m_MissionObjects[0].ClassName() == "SmallProtectorCase" )
			{
				if ( player.GetInventory().HasEntityInInventory( EntityAI.Cast( m_MissionObjects[0] ) ) && !m_ContainerWasTaken )
				{
					m_ContainerWasTaken = true;
					Print("[SMM] Mission object container was taken by a player ...and will be deleted.");
					GetGame().ObjectDelete( m_MissionObjects[0] );
				}
			}
		}
		
		//Check if container has desired amount of mushrooms collected at primary mission position
		if ( MissionObject && MissionObject.ClassName() == "SmallProtectorCase" && !m_MissionExtended )
		{
			int CargoCount = MissionObject.GetInventory().CountInventory();
			int LastCount = 0;
			int FoundObjects = 0;
			
			if ( CargoCount != LastCount )
			{
				if ( CargoCount >= ReqShroomsCount && FoundObjects <= ReqShroomsCount )
				{	
					CargoBase CargoItems1 = MissionObject.GetInventory().GetCargo();		
					
					for ( int i = 0; i < CargoCount; i++ )
					{
						EntityAI CargoItem = CargoItems1.GetItem(i);
						if ( m_MissionObjects.Find( CargoItem ) > -1 ) FoundObjects++;
						else continue;					
						
						//When requested amount of mushrooms is present, despawn MissionObject & spawn rewards
						if ( FoundObjects >= ReqShroomsCount )
						{
							Print("[SMM] Player with SteamID64: "+ player.GetIdentity().GetPlainId() +" has successfully stored the requested amount of "+ ReqShroomsCount +" MissionObjects in the container.");
							//delete container first
							GetGame().ObjectDelete( MissionObject );
							//call rewards spawn one second later 
							GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.SpawnRewards, 1000 );
							m_RewardsSpawned = true;
							m_MsgNum = -1;
							m_MsgChkTime = m_MissionTime + MsgDlyFinish;
							break;
						} 
					}
					LastCount = CargoCount;
				}
			} 
		}		
	}
		
	void UpdateBots(float dt)
	{
		//No bots involved in this mission		
	}
	
	bool DeployMission()
	{	//When first player enters the mission zone (primary/secondary)
		//Get MissionBuilding at mission position
		if ( !m_MissionExtended && !MissionBuilding )
		{
			GetGame().GetObjectsAtPosition( m_MissionPosition , 1.0 , m_ObjectList , m_ObjectCargoList );
			for ( int m=0; m < m_ObjectList.Count(); m++ )
			{ 
				Object FoundObject = m_ObjectList.Get(m);
				if ( FoundObject.GetType() == "Land_Village_PoliceStation_Enoch")
				{	
					MissionBuilding = FoundObject;			 
					Print("[SMM] MissionBuilding extended is "+ MissionBuilding.GetType() +" at "+ m_MissionDescription[3] +" @ "+ MissionBuilding.GetPosition() );
					
					//new MissionPosition is rewards spawnpoint
					m_MissionPosition = MissionBuilding.ModelToWorld( Spawnpoints.GetRandomElement() );
					break;
				}	
			}
		}	
			
		if ( (m_MissionPosition && m_MissionPosition != "0 0 0" && m_MissionExtended) || (MissionBuilding && !m_MissionExtended) )
		{
			//Call spawners	
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnObjects );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnAIs );
			return true;		
		}
		else 
		{
			Print("[SMM] Mission position was rejected or MissionBuilding doesn't exist!");
			if ( MissionSettings.DebugMode && !MissionBuilding && !m_MissionExtended ) Print("[SMM] MissionBuilding is NULL!");
			return false;
		}
	}
}

