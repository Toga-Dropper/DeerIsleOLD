# This file will only generate if disableBaseDamage is set to 0 in the serverdz.cfg
If you using older raiding meathods like breaching charges or seldge hammer actions this will have no affect
this will also not affect base building plus items
```js
[
    {
        "TypeName": "fence",  //this is the type name of the object
        "FireArms": 4.0,  //this is a modifier for how much damage a shooting the part will take
        "Melee": 0.1,  //This is a modifier for how much damage hitting the wall with melee will take
        "Explosive": 0.6,  //This is a modifier for how much damage explosive damage will do to a wall
        "Other": 0.0,  // Dayz has an other damage type so do i but not sure what this is for.
        "ToolsFirst": 1, // If set to one it will calcuate tool damage out put first then calcuate the parts, if 0 it will do part then tool
        "PartModifier": [  
            {
                "Part": "wall_wood",  // this is the part names partial matches also work
                "Modifier": 1.65,  // this is a modifier for damage done to this part
                "WhiteList": [  // this is a white list of items that can damage the wall (MUST BE ALL LOWERCASE)
					"m67Grenade",
					"rgd5grenade",
					"landminetrap",
					"bb_pipebomb",
					"firefighteraxe"
				],
                "RequiredDestroyed": []  //List items here that must be Destroyed before this part.
            },
            {
                "Part": "wall_metal",  
                "Modifier": 0.75,
                "WhiteList": [
                    "bb_pipebomb"
                ],
                "RequiredDestroyed": [
				]
            },
            {
                "Part": "wall_base_down",
                "Modifier": 45.0,
                "WhiteList": [
				],
                "RequiredDestroyed": [
					"wall_metal_down",
					"wall_wood_down"
				]
            },
            {
                "Part": "wall_base_up",
                "Modifier": 45.0,
                "WhiteList": [
				],
                "RequiredDestroyed": [
					"wall_metal_up",
					"wall_wood_up"
				]
            },
            {
                "Part": "*",
                "Modifier": 1.0,
                "WhiteList": [
					"m67Grenade",
					"rgd5grenade",
					"landminetrap",
					"bb_pipebomb",
					"firefighteraxe"
				],
                "RequiredDestroyed": []
            }
        ],
        "ToolModifiers": [
            {
                "Tool": "firefighteraxe",  //the tool or ammo used, note when using explosive or guns its recomended to use ammo since the melee actions with that item will count and might provide un expected results
                "Modifier": 10.0,  //Damage modifier for the tool
                "MinDmg": 20.0,  //Min Damage this item will do (keep in mind tool first if tools first it will be this min times the part modifier)
                "MaxDmg": 35.0, //Max Damage this item will do
                "MaxDistance": 4  //Max distance this item can be to do damage
            },
            {
                "Tool": "pipebomb_ammolow",
                "Modifier": 8.0,
                "MinDmg": 10000.0,
                "MaxDmg": 12500.0,
                "MaxDistance": 4
            },
            {
                "Tool": "pipebomb_ammohigh",
                "Modifier": 8.0,
                "MinDmg": 11000.0,
                "MaxDmg": 13000.0,
                "MaxDistance": 4
            },
            {
                "Tool": "pipebomb_ammo",
                "Modifier": 8.0,
                "MinDmg": 11000.0,
                "MaxDmg": 13000.0,
                "MaxDistance": 4
            }
        ]
    },
    {
        "TypeName": "watchtower",
        "FireArms": 0.3,
        "Melee": 0.1,
        "Explosive": 0.6,
        "Other": 0.0,
        "ToolsFirst": 1,
        "PartModifier": [
            {
                "Part": "wall_wood",
                "Modifier": 1.70,
                "WhiteList": [
					"m67Grenade",
					"rgd5grenade",
					"landminetrap",
					"bb_pipebomb",
					"firefighteraxe"
				],
                "RequiredDestroyed": []
            },
            {
                "Part": "wall_metal",
                "Modifier": 0.80,
                "WhiteList": [
                    "bb_pipebomb"
                ],
                "RequiredDestroyed": [
				]
            },
            {
                "Part": "wall_base_down",
                "Modifier": 55.0,
                "WhiteList": [
				],
                "RequiredDestroyed": [
					"wall_metal_down",
					"wall_wood_down"
				]
            },
            {
                "Part": "wall_base_up",
                "Modifier": 55.0,
                "WhiteList": [
				],
                "RequiredDestroyed": [
					"wall_metal_up",
					"wall_wood_up"
				]
            },
            {
                "Part": "*",
                "Modifier": 1.0,
                "WhiteList": [
					"m67Grenade",
					"rgd5grenade",
					"landminetrap",
					"bb_pipebomb",
					"firefighteraxe"
				],
                "RequiredDestroyed": []
            }
        ],
        "ToolModifiers": [
            {
                "Tool": "firefighteraxe",
                "Modifier": 11.0,
                "MinDmg": 22.0,
                "MaxDmg": 36.0,
                "MaxDistance": 4
            },
            {
                "Tool": "pipebomb_ammolow",
                "Modifier": 8.0,
                "MinDmg": 10000.0,
                "MaxDmg": 12500.0,
                "MaxDistance": 4
            },
            {
                "Tool": "pipebomb_ammohigh",
                "Modifier": 8.0,
                "MinDmg": 11000.0,
                "MaxDmg": 13000.0,
                "MaxDistance": 4
            },
            {
                "Tool": "pipebomb_ammo",
                "Modifier": 8.0,
                "MinDmg": 11000.0,
                "MaxDmg": 13000.0,
                "MaxDistance": 4
            }
        ]
    },
    {
        "TypeName": "*",
        "FireArms": 0.3,
        "Melee": 0.1,
        "Explosive": 1.0,
        "Other": 0.0,
        "ToolsFirst": 1,
        "PartModifier": [
            {
                "Part": "*",
                "Modifier": 1.0,
                "WhiteList": [],
                "RequiredDestroyed": []
            }
        ],
        "ToolModifiers": []
    }
	```
]
```