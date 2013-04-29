#ifndef GAMEDIALOGUE
#define GAMEDIALOGUE

#include <string>

using namespace std;

#include "Pokemon.h"
#include "CSVReader.h"
#include "PokemonBuilder.h"

string playerName;
string rivalName;
bool   isBoy;
int    myPokePetNum;
string petName;

Pokemon myPokemon(0,5);
CSVReader reader;
PokemonBuilder builder;

int curLocation;

const string npcName[]={	"Prof Haney",
							"Old Man",
							"Trainer",
							"PokeDrug Trainer",
							"Mayor",
							"Musician",
							"Dojo Master"};

const string badge[]={		"Rock Badge",
							"Water Badge",
							"Lighting Badge",
							"Field Badge",
							"Insect Badge",
							"Mind Badge",
							"Flame Badge",
							"Poison Badge"};


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
							"PokePet Flute"};

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
							"Route 12"};

const string yesNo[] = {"Yes",
						"No"};

//things trainers say when they lose
const string winLose[]={"You blacked out!", //use this when Player loses
						"What! How did I lose?",
						"Man, You're good.",
						"Even though I lost, that battle was fun",
						"You got lucky",
						"Aww..I was so close"
						"How did you get your PokePet to be so strong?"};

//things trainers say to Player
const string trainerQuote[]={	"Is that a PokePet? Lets battle!",
								"I love bug-type PokePets!",
								"I love rock-type PokePets!",
								"I love water-type PokePets!",
								"I love fire-type PokePets!",
								"I love grass-type PokePets!",
								"I love electric-type PokePets!",
								"I love ghost-type PokePets!",
								"I love ice-type PokePets!",
								"I love psychic-type PokePets!",
								"Are you a trainer too? Can we battle?",
								"You think you can beat me?"
								"Check out my new PokePet!",
								"YO LETS BATTLE,"
								"Can I test my PokePet against yours?",
								"Help me level up my PokePet!"};

const string rivalQuote[]={	//1st Rival Battle
							"Lets Battle! I know my PokePet is bettter than yours!", 
							//if Player wins
							"You got lucky this time...",
							"Why can't I win!",
							"Whatever, I'll beat you next time."
							//if Rival wins
							"Hmph, told you mine was better.",		
							"You're so weak!",
							"You seriously thought you could win? Hah"};

const string introText[]={	"Hello there!",
							"Welcome to the world of PokePets! My name is Haney!",
							"I study PokePets. People call me the PokePet Professor!",
							"This world is filled with creatures called PokePets!",
							"For some people, PokePets are just pets."
							"Others use them for fights!",
							"Oh sorry, I got so carried away that I didn't catch your name.",
								//get *playerName*

							"Are you a boy or girl?",
								//get *gender*

							"Hi *playerName*!",

							"You are about to embark on an incredible journey!",
							"But you also had a rival ever since you were young.",
							"Err.. what was *his/her* name again??",
								//get *rivalName*

							"Are you ready? Because your journey starts now!"};

const string palletTown[]={	"Prof Haney wants to talk to you!",
							"I want you to choose one of these PokePets and become good friends.",
							"Your Pokepet seems to like you.",
							"You should try to collect all the PokePet badges!",
							"Go past Viridian Forest to Pewter City and challenge the gym leader there"};

const string viridianCity[]={	"Gym is closed"};
								//add more text after 7 badges  


const string pewterCity[]={		"My name is Brock and I am the Pewter City Gym Leader.",
								"My rock-type PokePet is the toughest!"
								"If you want this badge, you gotta beat me first!",
								"Whoa you're really something...",
								"You beat me fair and square, here take this badge.",
								"The next gym is in Cerulean City.",
								"You can get there through going pass Mt.Moon via Route 3."};

//these are what Mr.X says to Player when they meet in Mt. Moon					
const string mtMoon[]={		"Perfect! With this drug, all the PokePets here will grow angry and stronger!",
							"Hmm..Who are you?",
							"Don't stand in my way or else..",
							"You're quite the trainer, but you're too late",
							"I'm done with what I wanted to accomplish here"};


const string ceruleanCity[]={	"My name is Misty and water-types are my specialty.",
								"There's no way you're getting this badge",
								"A win is a win, here take this with you",
								"Head to Vermillion City, The next gym you seek is there",
								"Thank you for stopping those PokeDrug Trainers",
								"Please take this PokePet as a reward"};


#endif
