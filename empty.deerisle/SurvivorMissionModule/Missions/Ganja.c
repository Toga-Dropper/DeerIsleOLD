class GanjaMission extends SurvivorMissions
{
	//Mission related entities 
	Car MissionCar;
	Object MissionBuilding;
	ItemBase MissionObject;
	
	//Mission parameters
	int ReqWeedAmount = 25;					//pieces, mission ganja (equivalent to x * 4 gramms)
	int ExtendedTimout = 1500;				//seconds, mission duration time for extended mission
	int MsgDlyFinish = 60;					//seconds, message delay time after player has finished mission
	
	//Mission containers
	ref array<vector> ExtendedPosList = new array<vector>;
	ref array<vector> GarageCarSpawns = new array<vector>;
	ref array<vector> Spawnpoints = new array<vector>;
	ref array<vector> PriInfectSpawns = new array<vector>;
	ref array<vector> SecInfectSpawns = new array<vector>;
	ref array<string> InfectedTypes = new array<string>;
	
	//Mission variables 
	string SurvivorName;	
	
	bool IsExtended() return true;
	
	void GanjaMission()
	{		
		//Select primary mission
		m_MissionExtended = true;
		
		//Mission timeout
		m_MissionTimeout = 2700;			//seconds, primary mission duration time
		
		//Mission zones
		m_MissionZoneOuterRadius = 150.0;	//meters (!Do not set lower than 200m), mission activation distance
		m_MissionZoneInnerRadius = 2.0;		//meters (!Do not set outside of 1-5m), mission finishing distance to target object
				
		//Mission informant
		m_MissionInformant = "Dr. Legasov";
	
		//Mission person names
		TStringArray SurvivorNames = {"Yuri","Michail","Boris","Valeri","Anatoli","Ivan","Alexej","Dimitrij","Sergej","Nikolai","Vladimir"};
		SurvivorName = SurvivorNames.GetRandomElement();
		
		//Set mission messages for primary mission
		m_MissionMessage1 = SurvivorName +", a guy who was working for me, told me that he has cross-breeded a special Cannabis strain of various 'Cannabis ruderalis' plants. I just need it for my experiments on the infected. He said that he fertilized the mother plants with shredded infected.";
		m_MissionMessage2 = "I think he meant any kind of fermented brew with water, infected ash and pieces of flesh done in a kitchen mixer. The impact on plants grow and bloom was massive. It also seems that it contains a substance other than the native Cannabinoids. I want to extract this substance to see how it acts on the infected.";
		m_MissionMessage3 = SurvivorName +" has hidden his herbs in a garage at\n** "+ m_MissionLocation +" **\nHe certainly has locked the garage doors, so try to use a lockpick or shoot them up if you have none.";
		
		//Spawnpoints for MissionCar in Garage 
		GarageCarSpawns.Insert("5.055 -1.504 -2.064"); 	//left garage
		GarageCarSpawns.Insert("-4.702 -1.504 -1.843");	//right garage
		
		//Spawnpoints for MissionObjects in middle garage (Do not change order!)
		Spawnpoints.Insert("1.575 -0.605 -5.431");  //on table right (3x motor oil)
		Spawnpoints.Insert("1.750 -0.605 -4.731");  //on table center (bag)
		Spawnpoints.Insert("1.800 -0.575 -3.8");	//on table left (weed pile)
		Spawnpoints.Insert("1.724 -1.504 -1.560");	//left beside table (gasoline canister)
		Spawnpoints.Insert("-1.85 -1.04 -2.196");	//shelf (spark plug)
		
		//Spawnpoint for reward container in Gas Station Building
		Spawnpoints.Insert("0.330 -1.538 0.6");		//beside desk
				
		//Infected spawnpoints for primary mission
		PriInfectSpawns.Insert("-10 0 20");
		PriInfectSpawns.Insert("-12 0 -30");
		PriInfectSpawns.Insert("20 0 -15");
		PriInfectSpawns.Insert("-30 0 -15");
		PriInfectSpawns.Insert("-16 0 -25");
		PriInfectSpawns.Insert("17 0 10");
		PriInfectSpawns.Insert("28 0 -30");
		
		//Infected spawnpoints for secondary mission 
		SecInfectSpawns.Insert("-11 0 -7");
		SecInfectSpawns.Insert("-8 0 8");
		SecInfectSpawns.Insert("8 0 -9");
		SecInfectSpawns.Insert("6 0 -5");
		SecInfectSpawns.Insert("18 0 15");
		
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
										
		//Search for mission building at primary mission position	
		GetGame().GetObjectsAtPosition( m_MissionPosition , 1.0 , m_ObjectList , m_ObjectCargoList );
		for ( int i = 0 ; i < m_ObjectList.Count(); i++ )
		{ 
			Object FoundObject = m_ObjectList.Get(i);
			if ( FoundObject.GetType() == "Land_Garage_Row_Small" )
			{	
				MissionBuilding = FoundObject;			 
				Print("[SMM] MissionBuilding is "+ MissionBuilding.GetType() +" at "+ m_MissionDescription[2] +" of "+ m_MissionDescription[1] +" @ "+ MissionBuilding.GetPosition() );
				break;
			}	
		}
		if ( !MissionBuilding ) Print("[SMM] Garage couldn't be found. Mission rejected!");
		else
		{
			//Close all garage doors
			Building Garage = Building.Cast( MissionBuilding );
			for ( int j=0; j < 3; j++ ) 
			{
				if ( Garage.IsDoorOpen(j) ) Garage.CloseDoor(j);
				if ( !Garage.IsDoorLocked(j) ) Garage.LockDoor(j); 
			}	
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( GetGame().UpdatePathgraphRegionByObject, 1000, false, Garage );		
		}			
	}
	
	void ~GanjaMission()
	{	
		//Despawn all remaining mission objects
		if ( m_MissionObjects )
		{
			Print("[SMM] Despawning "+ m_MissionObjects.Count() +" mission objects from old mission...");		
			for ( int i = 0; i < m_MissionObjects.Count(); i++ )
			{				
				if ( !m_MissionObjects.Get(i))	continue;
				else
				{	
					if ( m_MissionObjects.Get(i).IsTransport() ) 
					{
						//Don't delete just add full damage to MissionCar
						m_MissionObjects.Get(i).SetHealth("","",0);
						continue;
					}
							
					GetGame().ObjectDelete( m_MissionObjects.Get(i) );
				}			
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
	
	void SpawnCar()
	{		
		//Create MissionCar
		Print("[SMM] Spawning mission vehicle");
		
		MissionCar = Car.Cast(GetGame().CreateObject("OffroadHatchback", m_MissionPosition ));
		MissionCar.GetInventory().CreateAttachment("HatchbackWheel");
		MissionCar.GetInventory().CreateAttachment("HatchbackWheel");
		MissionCar.GetInventory().CreateAttachment("HatchbackWheel");
		MissionCar.GetInventory().CreateAttachment("HatchbackWheel");
		MissionCar.GetInventory().CreateAttachment("HatchbackWheel");
		MissionCar.GetInventory().CreateAttachment("HatchbackTrunk");
		MissionCar.GetInventory().CreateAttachment("HatchbackHood");
		MissionCar.GetInventory().CreateAttachment("HatchbackDoors_Driver");
		MissionCar.GetInventory().CreateAttachment("HatchbackDoors_CoDriver");
		MissionCar.GetInventory().CreateAttachment("CarRadiator");
		MissionCar.GetInventory().CreateAttachment("CarBattery");
		MissionCar.GetInventory().CreateAttachment("HeadlightH7");
		MissionCar.GetInventory().CreateAttachment("HeadlightH7");
		
		//Create car inventory
		MissionCar.GetInventory().CreateInInventory("Canteen");
		MissionCar.GetInventory().CreateInInventory("PersonalRadio");
		MissionCar.GetInventory().CreateInInventory("TireRepairKit");
		EntityAI kit = MissionCar.GetInventory().CreateInInventory("FirstAidKit");
			kit.GetInventory().CreateInInventory("TetracyclineAntibiotics");
			kit.GetInventory().CreateInInventory("BandageDressing");
			kit.GetInventory().CreateInInventory("Morphine");
		MissionCar.GetInventory().CreateInInventory("Battery9V");
		MissionCar.GetInventory().CreateInInventory("Battery9V");
		MissionCar.GetInventory().CreateInInventory("Battery9V");
		MissionCar.GetInventory().CreateInInventory("Battery9V");
		MissionCar.GetInventory().CreateInInventory("HeadlightH7");
		MissionCar.GetInventory().CreateInInventory("HeadlightH7");

		//Fill coolant with water
		MissionCar.Fill(CarFluid.COOLANT, 20.0 );
		
		//Set car orientation with rear to door 
		MissionCar.SetOrientation( MissionBuilding.GetOrientation() + "180 0 0" );
		
		//Set car CE lifetime
		MissionCar.SetLifetime( 3600 );	
		
		m_MissionObjects.InsertAt( MissionCar, 0 ); 		
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
					
		Print("[SMM] Mission rewards spawned in reward container. Randomly selected loadout was "+selectedLoadout+"." );			
	}
	
	void SpawnObjects()
	{	
		if ( m_MissionExtended )
		{	
			//Get random spawnpoint for car
			m_MissionPosition = MissionBuilding.ModelToWorld( GarageCarSpawns.GetRandomElement());
	 		
			//Clean up MissionCar spawnpoint
			GetGame().GetObjectsAtPosition( m_MissionPosition, 1.5, m_ObjectList, m_ObjectCargoList );
			
			if ( m_ObjectList.Count() > 0)
			{
				for ( int i=0; i < m_ObjectList.Count(); i++)
				{
					Object FoundObject = m_ObjectList.Get(i);
					if ( FoundObject.IsItemBase() )
					{
						Print("[SMM] BeforeSpawnCleanUp :: Object  " + FoundObject.ToString() + " at new mission position was deleted.");
						GetGame().ObjectDelete( FoundObject );
					}
				}
			}
			
			//Spawn car 1 second later			
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.SpawnCar, 1000 );
						
			//Spawn Ganja bag
			MissionObject = ItemBase.Cast( GetGame().CreateObject("CourierBag", MissionBuilding.ModelToWorld( Spawnpoints.Get(1) )));
			m_MissionObjects.InsertAt( MissionObject, 1 );			
			
			//Spawn mission vehicle related stuff
			Object CarStuff;
			
			CarStuff = GetGame().CreateObject("EngineOil", MissionBuilding.ModelToWorld( Spawnpoints.Get(0) ));
			CarStuff.SetOrientation( MissionBuilding.GetOrientation() + "-90 0 0");
			m_MissionObjects.InsertAt( CarStuff, 2 );
			CarStuff = GetGame().CreateObject("EngineOil", MissionBuilding.ModelToWorld( Spawnpoints.Get(0) + "0.2 0 0" ));
			CarStuff.SetOrientation( MissionBuilding.GetOrientation() + "-90 0 0");
			m_MissionObjects.InsertAt( CarStuff, 3 );			
			CarStuff = GetGame().CreateObject("EngineOil", MissionBuilding.ModelToWorld( Spawnpoints.Get(0) + "0.4 0 0" ));
			CarStuff.SetOrientation( MissionBuilding.GetOrientation() + "-90 0 0");
			m_MissionObjects.InsertAt( CarStuff, 4 );			
			m_MissionObjects.Insert( GetGame().CreateObject("CanisterGasoline", MissionBuilding.ModelToWorld( Spawnpoints.Get(3) )));
			m_MissionObjects.Insert( GetGame().CreateObject("SparkPlug", MissionBuilding.ModelToWorld( Spawnpoints.Get(4) )));		
			m_MissionObjects.Insert( GetGame().CreateObject("Wrench", MissionBuilding.ModelToWorld( Spawnpoints.Get(4) - "0 0 0.2" )));
			
			//Cluster spawn mission ganja 			
			for ( int j=0; j < ReqWeedAmount; j++ )
			{
				Object Ganja = GetGame().CreateObject("Cannabis", MissionBuilding.ModelToWorld( Spawnpoints.Get(2) ));
				vector gpos = { Math.RandomFloatInclusive(-0.3, 0.3), 0, Math.RandomFloatInclusive(-0.3, 0.3) };
				Ganja.SetPosition( MissionBuilding.ModelToWorld( Spawnpoints.Get(2) + gpos ) );
				m_MissionObjects.Insert( Ganja );
			}
			
			Print("[SMM] Survivor Mission "+ m_selectedMission +" :: "+ m_MissionName +" ...primary mission deployed!");
		}
		else
		{
			//Spawn nothing when player is entering secondary mission zone
				
			Print("[SMM] Survivor Mission Extension "+ m_selectedMission +" :: "+ m_MissionName +" ...secondary mission deployed!");
		}
	}
	
	void SpawnAIs()
	{	
		string RandomInfected;
		vector InfectedPos;
		DayZInfected Zed;
				
		if ( !MissionBuilding ) Print("[SMM] Extended Mission : Missionbuilding couldn't be found in "+ m_MissionDescription[3] +"." );		
		else
		{
			if ( m_MissionExtended )
			{
				//Spawn some infected at garage
				for ( int j = 0 ; j < PriInfectSpawns.Count() ; j++ )
				{
		    	   	RandomInfected = InfectedTypes.GetRandomElement();
					InfectedPos = MissionBuilding.ModelToWorld( PriInfectSpawns.Get(j) );
					Zed = DayZInfected.Cast( GetGame().CreateObject( RandomInfected, InfectedPos, false, true ));
					m_MissionAIs.Insert( Zed );
				}
			}
			else
			{
				//Spawn some infected at Gas station
				for ( int k = 0 ; k < SecInfectSpawns.Count() ; k++ )
				{
		    	   	RandomInfected = InfectedTypes.GetRandomElement();
					InfectedPos = MissionBuilding.ModelToWorld( SecInfectSpawns.Get(k) );
					Zed = DayZInfected.Cast( GetGame().CreateObject( RandomInfected, InfectedPos, false, true ));
					m_MissionAIs.Insert( Zed );
				}		
			}
		}
	}
	
	void ObjDespawn() 
	{	
		//Despawn all mission objects at mission timeout except those retains until next mission
		for ( int i = 0; i < m_MissionObjects.Count(); i++ )
		{
			//Exception: MissionCar will remain but gets damaged
			if ( m_MissionObjects.Get(i) && m_MissionObjects.Get(i).IsTransport() )	
			{
				m_MissionObjects.Get(i).SetHealth("","",0);
				continue;
			}
			
			//Delete Object
			GetGame().ObjectDelete( m_MissionObjects.Get(i) );
			m_MissionObjects.Remove(i);
		}
	}
	
	void ExtendMission()
	{	//When player enters mission target zone at primary mission
		
		//Set messages for secondary mission
		m_MissionMessage1 = "Allright, so you have found the car. "+ SurvivorName +" has probably drained all fuel and oil so prepare the car before that long trip. Check if the dried Cannabis is anywhere in the garages there and take the bag and put all 25 pieces in it.";
		m_MissionMessage2 = "Drive to the  ** "+ m_MissionDescription[3] +" Gas Station **\nand bring the Ganjabag to cash desk. "+ SurvivorName +"'s ganja has the highest priority. Please don't steal or smoke any of it by your own because it could be very dangerous.";
		m_MissionMessage3 = "I have some things for you at the gas station. Be carefull, there might be bandits on the way to "+ m_MissionDescription[3] +". They could intercepted our little radio talk here. Good luck and drive carefully!";
		
		//init Messenger for new messages
		m_MsgNum = 1;					//skip msg 0, begin with msg 1
		m_MsgChkTime = m_MissionTime;
		MsgCutoff = false;
		
		//increase mission MissionTimeout for secondary mission
		m_MissionTimeout = m_MissionTime + ExtendedTimout;  
		
		//deployment settings & init for secondary mission		
		m_MissionZoneOuterRadius = 80.0;
		m_MissionZoneInnerRadius = 2.0;
		
		//Get secondary mission position
		if ( m_MissionDescription[3] == "Widok" )
		{
			if ( EventsWorldData.GetBuildingsAtLoc("Land_FuelStation_Build", m_MissionDescription[3], ExtendedPosList ))
			m_MissionPosition = ExtendedPosList.GetRandomElement();			
		}
		else if ( EventsWorldData.GetBuildingsAtLoc("Land_FuelStation_Build_Enoch", m_MissionDescription[3], ExtendedPosList ))
		m_MissionPosition = ExtendedPosList.GetRandomElement();
		else Print("[SMM] Can't get secondary MissionPosition in "+ m_MissionDescription[3] +" from EventsWorldData!");
	}
	
	void MissionFinal()
	{	//When player enters last mission target zone
		//do nothing		
	}
	
	void PlayerChecks( PlayerBase player )
	{
		//Check if MissionObject is brought to MissionPosition 
		if ( MissionObject && MissionObject.ClassName() == "CourierBag" && !m_MissionExtended )
		{		
			float BagDistance = vector.Distance( MissionObject.GetPosition(), m_MissionPosition );
			if ( BagDistance < 3 )
			{
				int CargoCount = MissionObject.GetInventory().CountInventory();
				int LastCount = 0;
				int FoundObjects = 0;
				
				if ( CargoCount != LastCount )
				{
					if ( CargoCount >= ReqWeedAmount && FoundObjects <= ReqWeedAmount )
					{	
						CargoBase CargoItems1 = MissionObject.GetInventory().GetCargo();		
						
						for ( int i = 0; i < CargoCount; i++ )
						{
							EntityAI CargoItem = CargoItems1.GetItem(i);
							if ( m_MissionObjects.Find( CargoItem ) > -1 ) FoundObjects++;
							else continue;					
							
							//When requested amount of Ganja is present, despawn MissionObject & spawn rewards
							if ( FoundObjects >= ReqWeedAmount )
							{
								Print("[SMM] Player with SteamID64: "+ player.GetIdentity().GetPlainId() +" has successfully stored the requested amount of "+ ReqWeedAmount +" MissionObjects in the container.");
								//delete container first
								GetGame().ObjectDelete( MissionObject );
								//spawn rewards 
								SpawnRewards();
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
	}
		
	void UpdateBots( float dt )
	{
		//No bots involved in this mission		
	}
	
	bool DeployMission()
	{	//When first player enters the mission zone (primary/secondary)
		//Get MissionBuilding at secondary mission position
		if ( !m_MissionExtended )
		{			
			GetGame().GetObjectsAtPosition( m_MissionPosition , 1.0 , m_ObjectList , m_ObjectCargoList );
			for ( int i=0; i < m_ObjectList.Count(); i++ )
			{ 
				Object FoundObject = m_ObjectList.Get(i);
				if ( FoundObject.GetType() == "Land_FuelStation_Build_Enoch" || FoundObject.GetType() == "Land_FuelStation_Build")
				{			 
					MissionBuilding = FoundObject;
					Print("[SMM] MissionBuilding extended is "+ m_MissionDescription[3] +" Gas Station @ "+ m_MissionPosition );
					
					//new MissionPosition is rewards spawnpoint
					m_MissionPosition = MissionBuilding.ModelToWorld( Spawnpoints.Get(5) );
					break;
				}	
			}
		}
		
		if ( MissionBuilding )
		{
			//Call spawners	
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnObjects );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).Call( this.SpawnAIs );
			return true;		
		}
		else 
		{
			Print("[SMM] ERROR : MissionBuilding can't be found!");
			if ( MissionSettings.DebugMode ) Print("[SMM] MissionBuilding is NULL!");
			return false;
		}
	}
}
