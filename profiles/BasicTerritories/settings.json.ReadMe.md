```json
{
    "ConfigVersion": "1", 
    "WhiteList": [  //White list of items that can be placed anywhere this ingores no build zones and territories
        "Trap",
        "Paper",
        "Fireplace",
        "BB_PipeBomb",
        "LandmineTrap"
    ],
    "ServerAdmins": [  //This is the GUID for the admins who you want to be able to override territory permissions they can also reset territories
        "GUID"
    ],
    "TentRadius": 6.0,  // This will refresh the radius around a tent 0 disables radius
    "TentCESpawnLifeTime": 5600.0,  //This will set the lifetime of freshly spawned tents to this value to help them cycle through the economy 
    "BuildBonusSledgeDamage": 150.0, //This is bonus damage done to sledge hammers when building
    "RequireTerritory": 0,  // This will force players to need a territory to place items
	// Use https://daemonforge.dev/Calc/ to calculate the users permissions int 
    "PublicPermissions": 20,  // This is public permissions for all players within the territory
    "MemberPermissions": 30,  //this is the permissions that the members of the territory will get
    "Notifications": 1, //0 uses chat notifications 1 uses notifications mod
    "NoBuildZones": [
        {
            "X": 3703.5, 
            "Z": 5985.10986328125,
            "R": 100.0,
            "DrawOnMap": 0 //This will draw the area on the map if using basic map
        },
        {
            "X": 8345.6103515625,
            "Z": 5985.93017578125,
            "R": 100.0,
            "DrawOnMap": 0
        },
        {
            "X": 4007.90380859375,
            "Z": 11746.044921875,
            "R": 730.0,
            "DrawOnMap": 0
        },
        {
            "X": 4110.2509765625,
            "Z": 10983.96484375,
            "R": 620.0,
            "DrawOnMap": 0
        },
        {
            "X": 4498.59228515625,
            "Z": 10341.162109375,
            "R": 610.0,
            "DrawOnMap": 0
        },
        {
            "X": 4323.19775390625,
            "Z": 10640.365234375,
            "R": 650.0,
            "DrawOnMap": 0
        },
        {
            "X": 4770.84912109375,
            "Z": 9894.646484375,
            "R": 720.0,
            "DrawOnMap": 0
        },            
        {
            "X": 12101.939453125,
            "Z": 12632.1962890625,
            "R": 400.0,
            "DrawOnMap": 0
        },
        {
            "X": 2125.01318359375,
            "Z": 3373.494384765625,
            "R": 350.0,
            "DrawOnMap": 0
        },
        {
            "X": 5145.9287109375,
            "Z": 2281.958740234375,
            "R": 320.0,
            "DrawOnMap": 0
        },
        {
            "X": 4969.0732421875,
            "Z": 2493.201904296875,
            "R": 320.0,
            "DrawOnMap": 0
        },
        {
            "X": 7847.28662109375,
            "Z": 14704.1552734375,
            "R": 320.0,
            "DrawOnMap": 0
        },
        {
            "X": 949.0537719726563,
            "Z": 14670.228515625,
            "R": 320.0,
            "DrawOnMap": 0
        },
        {
            "X": 956.9163818359375,
            "Z": 13830.5546875,
            "R": 320.0,
            "DrawOnMap": 0
        },
        {
            "X": 1618.4561767578126,
            "Z": 14206.4736328125,
            "R": 650.0,
            "DrawOnMap": 0
        },
        {
            "X": 613.374267578125,
            "Z": 13639.482421875,
            "R": 300.0,
            "DrawOnMap": 0
        },
        {
            "X": 4541.50,
            "Z": 8299.80,
            "R": 260.0,
            "DrawOnMap": 0
        }
    ],
    "NoBuildZoneMessage": "You can't build here, are trying to build in a designated no build zones",
    "TerritoryConflictMessage": "Sorry you can't build a territory this close to another territory",
    "WithinTerritoryWarning": "Sorry you can't build this close to an enemy territory",    
	"DeSpawnWarningMessage": "You are building outside a territory, $ITEMNAME$ will despawn in $LIFETIME$ without a Territory\n\nLearn how to craft and build a territory, please check out our guide on discord - discord.gg/ youre discord", .. use $ITEMNAME$ for the items display name and $LIFETIME$ for the items lifetime
    "BuildPartWarningMessage": "Sorry, you don't have permissions to build in this area.",
    "DismantleWarningMessage": "Sorry, you can't dismantle anything this close to a raised flag",
    "LowerFlagWarningMessage": "Sorry, you do not have permissions to lower the flag in this territory",
    "TerritoryRequiredWarningMessage": "Sorry, you are required to build a territory to be able to build",
    "FlagRefreshFrequency": 432000,  //This should populate from your globals.xml any items less than this lifetime won't get warning messages and won't refresh with the territory
    "KitLifeTimes": {
        "watchtowerkit": 1814400, // Lifetimes for the items when the kit is different
        "fencekit": 1814400, // Lifetimes for the items when the kit is different
        "msp_": 1814400  // You can use partial matches to get multiple items at once
    }
}
```