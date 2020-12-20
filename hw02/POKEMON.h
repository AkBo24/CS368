#ifndef __POKEMON_H__
#define __POKEMON_H__

#include <vector>
#include <string>

using namespace std;

struct POKEMON {
	int attack;
	int defense;
	int hp;
	string name;
	string region;
	int special_attack;
	int special_defense;
	int speed;
	string type_1;
	string type_2;         
};

const int pcount = 94;

POKEMON pokemon_list[pcount] = {
    POKEMON{55,40,35,"Pikachu","Kanto",50,50,90,"Electric","None"},
    POKEMON{134,95,91,"Dragonite","Kanto",100,100,80,"Dragon","Flying"},
    POKEMON{65,60,60,"Gengar","Kanto",130,75,110,"Ghost","Poison"},
    POKEMON{70,40,40,"Riolu","Sinnoh",35,40,60,"Fighting","None"},
    POKEMON{50,77,50,"Rotom","Sinnoh",95,77,91,"Electric","Ghost"},
    POKEMON{49,49,45,"Bulbasaur","Kanto",65,65,45,"Grass","Poison"},
    POKEMON{52,43,39,"Charmander","Kanto",60,50,65,"Fire","None"},
    POKEMON{64,58,58,"Charmeleon","Kanto",80,65,80,"Fire","None"},
    POKEMON{84,78,78,"Charizard","Kanto",109,85,100,"Fire","Flying"},
    POKEMON{105,90,30,"Krabby","Kanto",25,25,50,"Water","None"},
    POKEMON{130,115,55,"Kingler","Kanto",50,50,75,"Water","None"},
    POKEMON{105,75,105,"Muk","Kanto",65,100,50,"Poison","None"},
    POKEMON{100,95,75,"Tauros","Kanto",40,70,110,"Normal","None"},
    POKEMON{110,65,160,"Snorlax","Kanto",65,110,30,"Normal","None"},
    POKEMON{125,75,80,"Heracross","Johto",40,95,85,"Bug","Fighting"},
    POKEMON{49,65,45,"Chikorita","Johto",49,65,45,"Grass","None"},
    POKEMON{62,80,60,"Bayleef","Johto",63,80,60,"Grass","None"},
    POKEMON{52,43,39,"Cyndaquil","Johto",60,50,65,"Fire","None"},
    POKEMON{64,58,58,"Quilava","Johto",80,65,80,"Fire","None"},
    POKEMON{65,64,50,"Totodile","Johto",44,48,43,"Water","None"},
    POKEMON{50,50,100,"Noctowl","Johto",86,96,70,"Normal","Flying"},
    POKEMON{60,60,90,"Phanpy","Johto",40,40,40,"Ground","None"},
    POKEMON{120,120,90,"Donphan","Johto",60,60,50,"Ground","None"},
    POKEMON{55,30,40,"Taillow","Hoenn",30,30,85,"Normal","Flying"},
    POKEMON{85,60,60,"Swellow","Hoenn",75,50,125,"Normal","Flying"},
    POKEMON{45,35,40,"Treecko","Hoenn",65,55,70,"Grass","None"},
    POKEMON{65,45,50,"Grovyle","Hoenn",85,65,95,"Grass","None"},
    POKEMON{85,65,70,"Sceptile","Hoenn",105,85,120,"Grass","None"},
    POKEMON{80,65,43,"Corphish","Hoenn",50,35,35,"Water","None"},
    POKEMON{85,140,70,"Torkoal","Hoenn",85,70,20,"Fire","None"},
    POKEMON{50,50,50,"Snorunt","Hoenn",50,50,50,"Ice","None"},
    POKEMON{80,80,80,"Glalie","Hoenn",80,80,80,"Ice","None"},
    POKEMON{55,30,40,"Starly","Sinnoh",30,30,60,"Normal","Flying"},
    POKEMON{75,50,55,"Staravia","Sinnoh",40,40,80,"Normal","Flying"},
    POKEMON{120,70,85,"Staraptor","Sinnoh",50,60,100,"Normal","Flying"},
    POKEMON{68,64,55,"Turtwig","Sinnoh",45,55,31,"Grass","None"},
    POKEMON{89,85,75,"Grotle","Sinnoh",55,65,36,"Grass","None"},
    POKEMON{109,105,95,"Torterra","Sinnoh",75,85,56,"Grass","Ground"},
    POKEMON{58,44,44,"Chimchar","Sinnoh",58,44,61,"Fire","None"},
    POKEMON{78,52,64,"Monferno","Sinnoh",78,52,81,"Fire","Fighting"},
    POKEMON{104,71,76,"Infernape","Sinnoh",104,71,108,"Fire","Fighting"},
    POKEMON{65,35,55,"Buizel","Sinnoh",60,30,85,"Water","None"},
    POKEMON{75,105,65,"Gligar","Johto",35,65,85,"Ground","Flying"},
    POKEMON{95,125,75,"Gliscor","Sinnoh",45,75,95,"Ground","Flying"},
    POKEMON{70,45,58,"Gible","Sinnoh",40,45,42,"Dragon","Ground"},
    POKEMON{55,50,50,"Pidove","Unova",36,30,43,"Normal","Flying"},
    POKEMON{77,62,62,"Tranquill","Unova",50,42,65,"Normal","Flying"},
    POKEMON{115,80,80,"Unfezant","Unova",65,55,93,"Normal","Flying"},
    POKEMON{55,45,55,"Oshawott","Unova",63,45,45,"Water","None"},
    POKEMON{63,45,65,"Tepig","Unova",45,45,45,"Fire","None"},
    POKEMON{93,55,90,"Pignite","Unova",70,55,55,"Fire","Fighting"},
    POKEMON{45,55,45,"Snivy","Unova",45,55,63,"Grass","None"},
    POKEMON{75,70,50,"Scraggy","Unova",35,70,48,"Dark","Fighting"},
    POKEMON{53,70,45,"Sewaddle","Unova",40,60,42,"Bug","Grass"},
    POKEMON{63,90,55,"Swadloon","Unova",50,80,42,"Bug","Grass"},
    POKEMON{103,80,75,"Leavanny","Unova",70,80,92,"Bug","Grass"},
    POKEMON{65,55,75,"Palpitoad","Unova",65,55,69,"Water","Ground"},
    POKEMON{75,85,55,"Roggenrola","Unova",25,25,15,"Rock","None"},
    POKEMON{105,105,70,"Boldore","Unova",50,40,20,"Rock","None"},
    POKEMON{82,45,60,"Krokorok","Unova",45,45,74,"Ground","Dark"},
    POKEMON{117,80,95,"Krookodile","Unova",65,70,92,"Ground","Dark"},
    POKEMON{50,43,45,"Fletchling","Kalos",40,38,62,"Normal","Flying"},
    POKEMON{73,55,62,"Fletchinder","Kalos",56,52,84,"Fire","Flying"},
    POKEMON{81,71,78,"Talonflame","Kalos",74,69,126,"Fire","Flying"},
    POKEMON{92,75,78,"Hawlucha","Kalos",74,63,118,"Fighting","Flying"},
    POKEMON{30,35,40,"Noibat","Kalos",45,40,55,"Flying","Dragon"},
    POKEMON{70,80,85,"Noivern","Kalos",97,80,123,"Flying","Dragon"},
    POKEMON{55,55,68,"Rowlet","Alola",50,50,42,"Grass","Flying"},
    POKEMON{65,40,45,"Rockruff","Alola",30,40,60,"Rock","None"},
    POKEMON{115,65,75,"Lycanroc","Alola",55,65,112,"Rock","None"},
    POKEMON{65,40,45,"Litten","Alola",60,40,70,"Fire","None"},
    POKEMON{85,50,65,"Torracat","Alola",80,50,90,"Fire","None"},
    POKEMON{115,90,95,"Incineroar","Alola",80,90,60,"Fire","Dark"},
    POKEMON{65,65,46,"Meltan","Alola",55,35,34,"Steel","None"},
    POKEMON{143,143,135,"Melmetal","Alola",80,65,34,"Steel","None"},
    POKEMON{48,65,44,"Squirtle","Kanto",50,64,43,"Water","None"},
    POKEMON{105,60,65,"Primeape","Kanto",60,70,95,"Fighting","None"},
    POKEMON{30,35,45,"Caterpie","Kanto",20,20,45,"Bug","None"},
    POKEMON{20,55,50,"Metapod","Kanto",25,25,30,"Bug","None"},
    POKEMON{45,50,60,"Butterfree","Kanto",90,80,70,"Bug","Flying"},
    POKEMON{60,55,63,"Pidgeotto","Kanto",50,50,71,"Normal","Flying"},
    POKEMON{80,75,83,"Pidgeot","Kanto",70,70,101,"Normal","Flying"},
    POKEMON{85,80,130,"Lapras","Kanto",85,95,60,"Water","Ice"},
    POKEMON{56,40,41,"Froakie","Kalos",62,44,71,"Water","None"},
    POKEMON{63,52,54,"Frogadier","Kalos",83,56,97,"Water","None"},
    POKEMON{95,67,72,"Greninja","Kalos",103,71,122,"Water","Dark"},
    POKEMON{50,35,45,"Goomy","Kalos",55,75,40,"Dragon","None"},
    POKEMON{75,53,68,"Sliggoo","Kalos",83,113,60,"Dragon","None"},
    POKEMON{100,70,90,"Goodra","Kalos",110,150,80,"Dragon","None"},
    POKEMON{73,67,67,"Poipole","Alola",73,67,73,"Poison","None"},
    POKEMON{73,73,73,"Naganadel","Alola",127,73,121,"Poison","Dragon"},
    POKEMON{81,60,55,"Raticate","Kanto",50,70,97,"Normal","None"},
    POKEMON{70,55,55,"Aipom","Johto",40,55,85,"Normal","None"},
    POKEMON{90,40,65,"Beedrill","Kanto",45,80,75,"Bug","Poison"}
};

int get_count() {return pcount;}
int get_attack(const int index) {return pokemon_list[index].attack;}
int get_defense(const int index) {return pokemon_list[index].defense;}
int get_hp(const int index) {return pokemon_list[index].hp;}
int get_special_attack(const int index) {return pokemon_list[index].special_attack;}
int get_special_defense(const int index) {return pokemon_list[index].special_defense;}
int get_speed(const int index) {return pokemon_list[index].speed;}
const string & get_name(const int index) {return pokemon_list[index].name;}
const string & get_region(const int index) {return pokemon_list[index].region;}
const string & get_type_1(const int index) {return pokemon_list[index].type_1;}
const string & get_type_2(const int index) {return pokemon_list[index].type_2;}

#endif
