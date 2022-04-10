class HordeMission extends SurvivorMissions
{
	//Mission related entities 
	ItemBase MissionObject;
	
	//Mission parameters
	int MsgDlyFinish = 300;					//seconds, message delay time after player has finished mission
	int HordeDensity = 60;					//infected, spawned in circle 
	
	//Mission containers
	ref array<string> InfectedTypes = new array<string>;

	//Mission variables 
			
	
	bool IsExtended() return false;
	
	void HordeMission()
	{
		//Mission mission timeout
		m_MissionTimeout = 2700;			//seconds, mission duration time
		
		//Mission zones
		m_MissionZoneOuterRadius = 200.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 3.0;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object
				
		//Mission informant
		m_MissionInformant = "Dr. Legasov";
		
		//Set mission messages
		m_MissionMessage1 = "I got an emergency call from a heli pilot who crashed somewhere in the forests. He is injured but still alive. He was afraid that the infected will find him soon.";
		m_MissionMessage2 = "He maid it to a house in a village near the crash site. He is well equiped and he think he will stay in the house over the night where he treats his open wounds.";
		m_MissionMessage3 = "The house is at the ** "+ m_MissionLocationDir +" side of "+ m_MissionLocation +" **\nBe careful there may be infected and other survivors who want his equipment!";
		

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
	
	void ~HordeMission()
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
	
	void SpawnObjects()
	{				
		//Mission object is pilot bag
		MissionObject = ItemBase.Cast( GetGame().CreateObject("AliceBag_Camo", m_MissionPosition ) );
		MissionObject.SetPosition( m_MissionPosition + "0 0.2 0" );
		//MissionObject.PlaceOnSurface(); 
		
		//Get random loadout 			
		int selectedLoadout = Math.RandomIntInclusive(0,11);	//!Change randomization limit after adding new loadouts!
		
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
		if (selectedLoadout == 10)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("TTC_AKM");
				weapon.GetInventory().CreateAttachment("AKS74U_Bttstck");			
			MissionObject.GetInventory().CreateInInventory("Mag_AKM_30Rnd");
			MissionObject.GetInventory().CreateInInventory("M67Grenade");
			MissionObject.GetInventory().CreateInInventory("M67Grenade");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackKush");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackKush");			
		}
		if (selectedLoadout == 11)
		{			
			weapon = MissionObject.GetInventory().CreateInInventory("Glock19");
				weapon.GetInventory().CreateAttachment("PistolSuppressor");			
			MissionObject.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
			MissionObject.GetInventory().CreateInInventory("Mag_Glock_15Rnd");
			MissionObject.GetInventory().CreateInInventory("FishingRod");
			MissionObject.GetInventory().CreateInInventory("Carp");
			MissionObject.GetInventory().CreateInInventory("Hook");
			MissionObject.GetInventory().CreateInInventory("Worm");
			MissionObject.GetInventory().CreateInInventory("CombatKnife");
			MissionObject.GetInventory().CreateInInventory("Canteen");	
			MissionObject.GetInventory().CreateInInventory("MackerelFilletMeat");
			MissionObject.GetInventory().CreateInInventory("CP_RollingPapers");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackKush");
			MissionObject.GetInventory().CreateInInventory("CP_CannabisSeedsPackKush");			
		}
						
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+ selectedLoadout +"." );
		
		m_MissionObjects.Insert( MissionObject );
		
		Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...mission deployed!");
	}
	
	void SpawnAIs()
	{	
		//Spawn pilot
		DayZInfected InfectedPilot = DayZInfected.Cast( GetGame().CreateObject( "ZmbM_CommercialPilotOld_Olive" , m_MissionPosition , false , true ));
			InfectedPilot.SetPosition( m_MissionPosition );
		//InfectedPilot.PlaceOnSurface();
			InfectedPilot.GetInventory().CreateAttachment("ZSh3PilotHelmet_Green");
			InfectedPilot.GetInventory().CreateInInventory("M67Grenade");
			InfectedPilot.GetInventory().CreateInInventory("CanOpener");
			InfectedPilot.GetInventory().CreateInInventory("BandageDressing");
			InfectedPilot.GetInventory().CreateInInventory("PeachesCan");
			InfectedPilot.GetInventory().CreateInInventory("Canteen");
			InfectedPilot.GetInventory().CreateAttachment("UKAssVest_Olive");
			InfectedPilot.GetInventory().CreateInInventory("PersonalRadio");
			InfectedPilot.GetInventory().CreateInInventory("Battery9V");
			InfectedPilot.GetInventory().CreateInInventory("Battery9V");
			InfectedPilot.GetInventory().CreateInInventory("Battery9V");
			
		//Pilot is dead
		InfectedPilot.SetHealth("","",0);
		
		m_MissionAIs.Insert( InfectedPilot );
		
		//Spawn horde
		for ( int j = 0; j < HordeDensity; j++ )
		{
			//calc new spawn position
			float x = Math.RandomFloatInclusive( 3 , 30 );
			float y = Math.RandomFloatInclusive( 3 , 30 );	
			int Dice = Math.RandomIntInclusive( 0, 9);
			if ( Dice > 4 ) x *= -1.0;
			Dice = Math.RandomIntInclusive( 0, 9);
			if ( Dice < 5 ) y *= -1.0;
			vector NewPosVector = { x, 0, y };
			
			//Spawn infected
			m_MissionAIs.Insert( GetGame().CreateObject( InfectedTypes.GetRandomElement(), m_MissionPosition + NewPosVector, false, true ));	
		}
	}
	
	void ObjDespawn() 
	{	
		//nothing to despawn
	}
	
	void MissionFinal()
	{	//When player enters last mission target zone	

		//Alert infected 
//		for ( int j = 1 ; j < m_MissionAIs.Count(); j++ )
//		{
//			DayZInfected Zed = DayZInfected.Cast( m_MissionAIs.Get(j));
//			if ( Zed )
//			{
//				DayZInfectedCommandMove moveCommandZ = Zed.GetCommand_Move();
//				moveCommandZ.SetIdleState(2);
//			}
//		}
		
		//Finish mission
		m_RewardsSpawned = true;
		m_MsgNum = -1;
		m_MsgChkTime = m_MissionTime + MsgDlyFinish;			
	}
	
	void PlayerChecks( PlayerBase player )
	{
		
	}
		
	void UpdateBots(float dt)
	{
			
	}
	
	bool DeployMission()
	{	//When first player enters the mission zone (primary/secondary)
		if ( m_MissionPosition && m_MissionPosition != "0 0 0" )
		{
			//Call spawners	
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnObjects );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.SpawnAIs, 1000, false );
			return true;		
		}
		else 
		{
			Print("[SMM] ERROR : Mission position was rejected or doesn't exist. MissionPosition is NULL!");
			return false;
		}
	}
}

