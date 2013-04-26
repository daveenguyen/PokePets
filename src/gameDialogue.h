#ifndef GAMEDIALOGUE
#define GAMEDIALOGUE

#include <string>
#include <iostream>

using namespace std;

class gameDialogue
{`
	public:
		const string playName;
		
		const string rivalName;

		const string gender;
		
		const string npcName[]={	"Prof Haney",
									"Old Man",
									"Trainer",
									"PokeDrug Trainer",
									"Mayor",
									"Musician",
									"Dojo Master"};

		const string badge[]={		"Rock Badge",}
									"Water Badge",
									"Lighting Badge",
									"Field Badge",
									"Insect Badge",
									"Mind Badge",
									"Flame Badge",
									"Poison Badge",


		const string gymLeader[]={	"Brock",
									"Misty",
									"Lt. Serge",
									"Ericka",
									"Koga",
									"Sabrina",
									"Blain",
									"Mr. X"};
		
		const string eliteFour[]={	"Dale",
									"Davee",
									"Albert",
									"Angel"};
		
		const string action[]={		"Visit",
									"Go to",
									"Fly to",
									"Surf to"};

		const string item[]={		"Potion",
									"Max Potion",
									"Antidote",
									"Paralyz Heal",
									"Awakening",
									"Burn Heal",
									"Ice Heal",
									"Full Heal"
									"Ether",
									"Max Ether",
									"Full Restore"};

		const string specialItem[]={"HM Fly",
									"HM Surf",
									"PokePet Flute"}

		const string location[]={	"Pallet Town",
									"Viridian City",
									"Pewter City",
									"Cerulean City",
									"Vermillion City",
									"Lavendar Town",
									"Celadon City",
									"Fuchsia City",
									"Saffron City",
									"Cinnebar Island",
									"PokePet League"};

		const string place[]={		"Home",
									"Prof Haney's Lab",
									"PokePet Center",
									"PokePet Mart",
									"Gym"
									"Mt.Moon",
									"Rock Tunnel",
									"Underground Passage to Vermillion",
									"Underground Passage to Celadon",
									"Ghost Tower",
									"Abandoned Lab",
									"Dojo",
									"Crystal Cave"};
		
		const string route[]={		"Route 1",
									"Route 2",
									"Route 3",
									"Route 4",
									"Route 5",
									"Route 6",
									"Route 7",
									"Route 8",
									"Route 9",
									"Route 10",
									"Route 11",
									"Route 12",}

		const string introText[]={	"Hello there!
									Welcome to the world of PokePets! My name is Haney!
									I study PokePets. People call me the PokePet Professor!
									This world is filled with creatures called PokePets!
									For some people, PokePets are just pets. Others use them for fights!
									Oh sorry, I got so carried away that I didn't catch your name.",
									
										//get *playerName*
									"Are you a boy or girl",
										//get *gender
									
									"Hi",
										//*playerName
									
									"You are about to embark on an incredible journey!
									But you also had a rival ever since you were young.
									Err.. what was *his/her* name again??",
										//get *rivalName*

									"Are you ready? Because your journey starts now!"};

		const string palletTown[]={	""}


};



#endif
