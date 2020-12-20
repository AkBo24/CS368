#include <iostream>
#include "POKEMON.h"
#include <string>

using namespace std;

//Headers
int getStatTotal(string pok);
int getPokIdx(string pok); 
string simpleBattle(string pok1, string pok2);
string wildBattle(string pok1, string pok2);
string battle(string pok1, string pok2);
string final_battle(string pok1, string pok2);
float most_damage(string, string);

int main() {
  
    // To get started and see the format required for the answers, I've done the first question for you 
    cout<<"#Q1"<<endl;
    cout<<get_name(0)<<endl;
    cout<<endl;

    //continue from here by finding the index of Metapod
    cout<<"#Q2"<<endl;
    cout<< getPokIdx("Metapod")  <<endl;
    cout<<endl;

    cout<<"#Q3"<<endl;
    cout<<simpleBattle("Snorunt","Starly") << endl;  
    cout<<endl;

    cout<<"#Q4"<<endl;
    cout<<simpleBattle("Snorunt","Staravia") << endl;  
    cout<<endl;
    
    cout<<"#Q5"<<endl;
    cout<<simpleBattle("Charmander","Chimchar")<<endl;
    cout<<endl;

    cout<<"#Q6"<<endl;
    cout<<wildBattle("Caterpie","Melmetal") <<endl;
    cout<<endl;
    
    cout<<"#Q7"<<endl;
    cout<<wildBattle("Dragonite","Snorunt") <<endl;
    cout<<endl;

    cout<<"#Q8"<<endl;
    printf("%.2f\n", most_damage("Scraggy","Tranquill"));
    cout<<endl;

    cout<<"#Q9"<<endl;
    printf("%.2f\n", most_damage("Dragonite","Rockruff"));
    cout<<endl;

    cout<<"#Q10"<<endl;
    printf("%.2f\n", most_damage("Quilava","Grovyle"));
    cout<<endl;
   
    cout<<"#Q11"<<endl;
    printf("%.2f\n", most_damage("Goomy","Beedrill"));
    cout<<endl;

    cout<<"#Q12"<<endl;
    printf("%.2f\n", most_damage("Tepig","Charizard"));
    cout<<endl; 

    cout<<"#Q13"<<endl;
    cout << battle("Scraggy", "Krabby") << endl;
    cout<<endl;

    cout<<"#Q14"<<endl;
    cout << battle("Charizard", "Krabby") << endl;
    cout<<endl;

    cout<<"#Q15"<<endl;
    cout << battle("Treecko", "Litten") << endl;
    cout<<endl;

    cout<<"#Q16"<<endl;
    cout << battle("Treecko", "Buizel") << endl;
    cout<<endl;

    cout<<"#Q17"<<endl;
    cout << final_battle("Grotle", "Roggenrola") << endl;
    cout<<endl;

    cout<<"#Q18"<<endl;
    cout << final_battle("Starly", "Goodra") << endl;
    cout<<endl;


};

int getStatTotal(string pkmn) {
    int pok = getPokIdx(pkmn);

    if(pok == -1) return -1;

    return (get_attack(pok) + get_defense(pok) + get_hp(pok)+ 
            get_special_attack(pok) + get_special_defense(pok)  + get_speed(pok));
}

int getPokIdx(string pok) {
    int count = get_count(); 
    for(int i = 0; i < count; i++) {
        if(get_name(i).compare(pok) == 0)
            return i;
    }
    return -1;
}

string simpleBattle(string pok1, string pok2) {
    int s1 = getStatTotal(pok1), s2 = getStatTotal(pok2);

    //check both pokemon exist
    if(s1 == -1 || s2 == -1) return s1==-1?pok1:pok2;
    if(s1 > s2)      
        return pok1;
    else if(s2 > s1) 
        return pok2;
    return "Draw";

}

string wildBattle(string pok1, string pok2) {
    int s1 = getStatTotal(pok1), s2 = getStatTotal(pok2);

    //check both pokemon exist
    if(s1 == -1 || s2 == -1) return s1==-1?pok1:pok2;
    if(s1 - s2 > 300)
        return pok2 + " ran away";
    else if(s2 - s1 > 300)
        return pok1 + " ran away";
    return simpleBattle(pok1, pok2);

}

string battle(string pkmn1, string pkmn2) {
   //determine who goes first
   int p1Idx = getPokIdx(pkmn1), p2Idx = getPokIdx(pkmn2);
   float p1spd = get_speed(p1Idx), p2spd = get_speed(p2Idx);
   float p1HP = get_hp(p1Idx), p2HP = get_hp(p2Idx);
   int turn = 0; //switch which pokemon attacks
   int alpha = pkmn1.compare(pkmn2);

   if(p1spd > p2spd) goto pk1first;
   else if(p2spd > p1spd) goto pk2first;
   else if(p1spd == p2spd && alpha < 0) goto pk1first; 
   else if(p1spd == p2spd && alpha > 0) goto pk2first;

   pk1first: while(true) {
        if(turn % 2 == 0) {
            p2HP -= most_damage(pkmn1, pkmn2);
            turn ++;
            goto checkHP1;
        }
        p1HP -= most_damage(pkmn2, pkmn1);
        turn++;

        checkHP1: if(p1HP < 0) return pkmn2;
        else if(p2HP < 0) return pkmn1;
   }

   pk2first: while(true){
        if(turn % 2 != 0) {
            p2HP -= most_damage(pkmn1, pkmn2);
            turn ++;
            goto checkHP2;
        }
        p1HP -= most_damage(pkmn2, pkmn1);
        turn++;

        checkHP2: if(p1HP < 0) return pkmn2;
        else if(p2HP < 0) return pkmn1;
    
   }
}

string final_battle(string pkmn1, string pkmn2) {
    int p1Idx = getPokIdx(pkmn1), p2Idx = getPokIdx(pkmn2);
    if(get_region(p1Idx) != get_region(p2Idx) &&
            (get_type_1(p1Idx) == "Flying" || get_type_2(p1Idx) == "Flying" || get_type_1(p2Idx) == "Flying" || get_type_2(p2Idx) == "Flying"))
        return battle(pkmn1, pkmn2);
    return "Cannot Battle";
}

float most_damage(string pkmn1, string pkmn2) {
    int attacker = getPokIdx(pkmn1), defender = getPokIdx(pkmn2);
    float physical_damage = (float) 10 * get_attack(attacker)/get_defense(defender);
    float special_damage  = (float) 10 * get_special_attack(attacker)/get_special_defense(defender);
    return physical_damage > special_damage?physical_damage:special_damage;
}
