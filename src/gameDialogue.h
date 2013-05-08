#ifndef GAMEDIALOGUE
#define GAMEDIALOGUE

#include <string>

using namespace std;

#include "Pokemon.h"
#include "CSVReader.h"
#include "PokemonBuilder.h"

// Game Variables
string playerName;
string rivalName;
string petName;
bool   isBoy;
int    myPokePetNum;
int    rivalNum;
int    badgeCount;
int    itemCount[7];
int    curLocation;

// Pokemon myPokemon(0,5);
Pokemon*       myPokemon;
CSVReader      reader;
PokemonBuilder builder;


// menu strings
const string yesNo[] = {
	"Yes",
	"No"
};

const string menuOption[] = {
	"Travel",
	"Play",
	"Feed",
	"Clean",
	"Check Pet",
	"Battle",
	"Quit"
};

const string playMenu[] = {
	"Rock Paper Scissors",
	"Heads or Tails",
	"Guessing Game",
	"Cancel"
};

const string feedMenu[] = {
	"Berries",
	"Poffins",
	"Ice Cream",
	"Soda Pop",
	"Lemonade",
	"Water",
	"Rare Candy",
	"Cancel"
};

const string cleanMenu[] = {
	"Antidote Spray",
	"Awakening Spray",
	"Anti-Paralyze Spray",
	"Unburn Spray",
	"Unfreeze Spray",
	"Bath",
	"Cancel"
};

const string checkPetMenu[] = {
	"Check Pet Battle Info",
	"Check Pet Status",
	"Cancel"
};

const string npcName[]={
	"Prof Haney",
	"Old Man",
	"Trainer",
	"PokeDrug Trainer",
	"Mayor",
	"Musician",
	"Dojo Master"
};

// game menu
const string rpsMenu[] = {
	"Rock",
	"Paper",
	"Scissors"
};

const string htMenu[] = {
	"Head",
	"Tail"
};



const string gameResult[] = {
	"You Lose!",
	"You Win!",
	"Draw!"
};



// done menu strings

const string badge[]={
	"Rock Badge",
	"Water Badge",
	"Lighting Badge",
	"Field Badge",
	"Insect Badge",
	"Mind Badge",
	"Flame Badge",
	"Poison Badge"
};


const string gymLeader[]={
	"Brock",
	"Misty",
	"Lt. Surge",
	"Erika",
	"Koga",
	"Sabrina",
	"Blaine",
	"Mr. X"
};

const string eliteFour[]={
	"Dale",
	"Davee",
	"Albert",
	"Angel"
};

const string action[]={
	"Visit",
	"Go to",
	"Fly to",
	"Surf to"
};

// not using
// const string item[]={
// 	"Potion",
// 	"Max Potion",
// 	"Antidote",
// 	"Paralyze Heal",
// 	"Awakening",
// 	"Burn Heal",
// 	"Ice Heal",
// 	"Full Heal"
// 	"Ether",
// 	"Max Ether",
// 	"Full Restore"
// };

const string specialItem[]={
	"HM Fly",
	"HM Surf",
	"PokePet Flute"
};

const int wildPokePet[][8]={
	{0},								//Pallet Town
	{16,16,16,16,19,19,19,19},			//Route 1
	{0},								//Viridian City
	{29,29,29,32,32,56,21,21},			//Route 2
	{10,10,11,12,14,16,25,17},			//Viridian Forest
	{0},								//Pewter City
	{21,21,21,19,19,19,39,39},			//Route 3
	{41,41,35,74,74,74,95,95},			//Mt Moon
	{0},								//Cerulean City
	{63,63,63,96,43,48,69,54},			//Route 4
	{66,27,23,81,100,20,29,32},			//Route 5
	{0},								//Underground Passage
	{0},								//Vermillion City
	{17,96,96,96,19,22,22,22}, 			//Route 6,snorlax is on this route; need pokeflute
	{66,74,74,74,50,50,50,41}, 			//Rock Tunnel
	{0},								//Lavendar Town
	{92,92,92,92,92,93,104,104},		//Ghost Tower
	{52,52,52,58,37,37,39,63},			//Route 7
	{0},								//Underground Passage, Player recieves fly from old man
	{0},								//Celadon City
	{84,84,84,21,88,88,88,88},			//Route 8
	{0},								//Fuchsia City
	{123,77,77,46,46,83,83,102},		//Route 9
	{111,111,114,114,113,132,132,132},	//Route 10
	{0},								//Saffron City
	{0},								//Cinnebar Island
	{129,129,129,72,72,118,116,120},	//Route 11
	{90,90,79,79,131,86,60,98},			//Route 12
	{126,140,138,115,128,128,124,125},	//Crystal Cave
	{0},								//PokePet League
};

const int levelRange[][2]={
	{0},						//Pallet Town
	{3,4},						//Route 1
	{0},						//Viridian City
	{6,7},						//Route 2
	{7,10},						//Viridian Forest
	{0},						//Pewter City
	{12,14},					//Route 3
	{14,15},					//Mt Moon
	{0},						//Cerulean City
	{16,18},					//Route 4
	{19,22},					//Route 5
	{0},						//Underground Passage
	{0},						//Vermillion City
	{18,22}, 					//Route 6,snorlax(lvl30) is on this route; need pokeflute
	{22,23}, 					//Rock Tunnel
	{0},						//Lavendar Town
	{21,24},					//Ghost Tower
	{21,24},					//Route 7
	{0},						//Underground Passage, Player recieves fly from old man
	{0},						//Celadon City
	{28,33},					//Route 8
	{0},						//Fuchsia City
	{33,36},					//Route 9
	{36,38},					//Route 10
	{0},						//Saffron City
	{0},						//Cinnebar Island
	{38,40},					//Route 11
	{40,42},					//Route 12
	{43,45},					//Crystal Cave
	{0},						//PokePet League
};

const string location[]={
	"Pallet Town",
	"Route 1",
	"Viridian City",
	"Route 2",
	"Viridian Forest",
	"Pewter City",
	"Route 3",
	"Mt.Moon",
	"Cerulean City",
	"Route 4",
	"Route 5",
	"Underground Passage to Vermillion",
	"Vermillion City",
	"Route 6",
	"Rock Tunnel",
	"Lavendar Town",
	"Ghost Tower",
	"Route 7",
	"Underground Passage to Celadon",
	"Celadon City",
	"Route 8",
	"Fuchsia City",
	"Route 9",
	"Route 10",
	"Saffron City",
	"Cinnebar Island",
	"Route 11",
	"Route 12",
	"Crystal Cave",
	"PokePet League"
};

//things trainers say when they lose
const string winLose[]={
	"You blacked out!", //use this when Player loses
	"What! How did I lose?",
	"Man, You're good.",
	"Even though I lost, that battle was fun",
	"You got lucky",
	"Aww..I was so close"
	"How did you get your PokePet to be so strong?"
};

//things trainers say to Player before battle! or when encountered
const string trainerQuote[]={
	// "Is that a PokePet? Lets battle!",
	// "I love bug-type PokePets!",
	// "I love rock-type PokePets!",
	// "I love water-type PokePets!",
	// "I love fire-type PokePets!",
	// "I love grass-type PokePets!",
	// "I love electric-type PokePets!",
	// "I love ghost-type PokePets!",
	// "I love ice-type PokePets!",
	// "I love psychic-type PokePets!",
	"Are you a trainer too? Can we battle?",
	"You think you can beat me?"
	"Check out my new PokePet!",
	"YO LETS BATTLE,"
	"Can I test my PokePet against yours?",
	"Help me level up my PokePet!",
	//pokedrug trainers
	"Try and stop us!",
	"You're too late! We already drugged the river!",
	"Why are you trying to stop us?"
};

const string rivalQuote[]={
	//1st Rival Encounter
	"Lets Battle! I know my PokePet is bettter than yours!",
	//2nd Rival Encounter
	"There are PokeDrug trainers up ahead.",
	"I'll stop them myself AFTER I beat you!",
	//3rd Rival Encounter
	"Are you here to find the treasure too?",
	"I couldn't find it, so you should just give up.",
	"Smell you later!",
	//4th Rival Encounter
	"I am the strongest trainer in the WORLD! I AM THE CHAMPION!",
	//if Player wins
	"You got lucky this time...",
	"Why can't I win!",
	"Whatever, I'll beat you next time.",
	//if Rival wins
	"Hmph, told you mine was better.",
	"You're so weak!",
	"You seriously thought you could win? Hah"
};

const string introText[]={
	"Hello there!",
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

	"Are you ready? Because your journey starts now!"
};

const string palletTown[]={
	"Prof Haney wants to talk to you!",
	"I want you to choose one of these PokePets and become good friends.",
	"Your Pokepet seems to like you.",
	"You should try to collect all the PokePet badges!",
	"Go past Viridian Forest to Pewter City and challenge the gym leader there"
};


const string viridianCity[]={
	//need 7 badges for gym to open
	"Gym is closed",
	//after 7 badges obtained
	"Surprised to see me?",
	"I am the Viridian City gym leader.",
	"Even though you stopped my plans, I still have a duty to do as a gym leader",
	"You won't be getting this last badge!"
	//after win
	"Fascinating...your PokePets seem to find power through a different way....",
	"As much as I hate to do it, I have to give you this badge"
};


const string pewterCity[]={
	"My name is Brock and I am the Pewter City Gym Leader.",
	"My rock-type PokePet is the toughest!"
	"If you want this badge, you gotta beat me first!",
	//After win
	"Whoa you're really something...",
	"You beat me fair and square, here take this badge.",
	"The next gym is in Cerulean City.",
	"You can get there through going pass Mt.Moon via Route 3."
};

//these are what Mr.X says to Player when they meet in Mt. Moon
const string mtMoon[]={
	"Perfect! With this drug, all the PokePets here will grow angry and stronger!",
	"Hmm..Who are you?",
	"Don't stand in my way or else..",
	//after Player wins
	"You're quite the trainer, but you're too late",
	"I'm done with what I wanted to accomplish here"
	}; //Mr. X escapes


const string ceruleanCity[]={
	"My name is Misty and water-types are my specialty.",
	"There's no way you're getting this badge",
	//After win
	"A win is a win, here take this with you",
	"Head to Vermillion City, The next gym you seek is there",
	"Thank you for stopping those PokeDrug Trainers",
	"Please take this PokePet as a reward"
};

const string vermillionCity[]={
	"I'm Lt. Surge and I use electric-type PokePets",
	"You have no chance against me!",
	"You're pretty tough after all",
	"The next gym is located in Celadon City.",
	"Take this badge and Go!"
};

//when Player tries to wake up snorlax in Route 6
const string oldMan[]={
	"I saw you trying to wake that sleeping Pokepet.",
	"You're going to need a special instrument to wake it up.",
	"I heard a man in Lavendar Town has one.",
	"You can get there by going through Rock Tunnel.",
	//When player goes into Underground Passage to Celadon
	"I love flying! Here take this!"
};

//const string lavendarTown[]={	""}
//musician is in Lavendar Town
const string musician[]={
	"You want this PokePet Flute?",
	"If you find me the hidden treasure located in the GhostTower, then I'll trade for it.",
	"Hey is that the treasure?",
	"Here! take this flute!"
	}; // Player can now wake up snorlax

//these are what Mr.X says to Player when they meet in GhostTower
const string ghostTower[]={
	"We meet again...",
	"Soon all the ghost PokePet in this tower will grow with anger.",
	"You need to get out of my way",
	//After Player wins
	"Even though I lost, you're still too late.",
	"Soon this world will be filled with anger."
	}; //Mr. X escapes

const string celadonCity[]={
	"Ericka is my name and my grass-type PokePets are no joke.",
	"You better get ready to lose!",
	//After win
	"I can't believe I lost...oh wells.",
	"Please accept this badge as proof of victory."
	"You should head to Fuschia City next, Good luck."
};

const string fuchsiaCity[]={
	"People call me Koga, the bug-type specialist!",
	"I will swam you with bugs!",
	//After win
	"You battled well.",
	"Take this, it's yours now.",
	"The next gym is located at Cinnebar Island, but you'll need a PokePet that knows how to surf."
};

//story to go to saffron city, after fuchsia city
const string profHaney[]={
	"I need your help!",
	"My old college, Leo, is up to something terrible!",
	"You probably know him as Mr. X",
	"His lab is in Saffron City! Hurry and stop him!"
};

//Player needs to finish Abandoned Lab before entering Gym
const string saffronCity[]={
	"You can't come in",

	"I knew you were coming...My psychic-type PokePets told me",
	"I can predict your every move!",
	"You can't win!",
	//After win
	"I sense a strong will within you.",
	"Take this badge as proof that you beat me.",};

const string abandonedLab[]={
	"AHh..I was expecting you.",
	"Prof Haney sent you didn't he.",
	"That poor man just doesn't understand anymore."
	//After win
	"It's such a shame...",
	"With your talent, and my ideas, we could rule the world.",
	"Let us meet again someday."
};

const string cinnebarIsland[]={
	"Is it just me..or is it hot in here?",
	"Oh wait, its probably just my fire-type PokePets",
	"I hope you brought some burn heals"
	//After win
	"I can sense the flames in your passion for battling",
	"Careful with this badge, its HOT!",
	"I heard the gym in Viridian City is open again.",
	"I wonder what happened..."
};

const string Dale[]={
	"Welcome to the Elite Four.",
	"My name is Dale and I will show you that my electric-type PokePets are the strongest you'll ever fight.",
	"Let me teach you things you'll surely forget!"
	//after win
	"Hmm...I'll buy that."
};

const string Davee[]={
	"Haha so you beat Dale? My name is Davee and I created this game! ",
	"Damn I should of made this game harder"
};

const string Albert[]={
	"Yo! My name is Albert and my dragons are the strongest!",
	"Dragons are superior to everything!",
	"I'm gonna mess you up",
	//after win
	"You proven you can beat the best. Go on."
};

const string Angel[]={
	"Hmm..someone actually beat Albert?",
	"Damn just when I was going to go to sleep too...",
	"Lets get this over with.",
	//after win
	"RIGHTEOUS bro"
};

#endif
