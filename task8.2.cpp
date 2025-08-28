#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class weapons{
public:
    // attributes of the class weapons
    std::string name;
    int damage;
    int accuracy;

    // default constructor to call for each weapon
    weapons(std::string n, int d, int a) : name(n), damage(d), accuracy(a) {}

    weapons() : name("None"), damage(0), accuracy(0) {}

    bool attack() const{
        int random = rand() % 100 +1;  //generates a random integer from 1 to 100
        return random <= accuracy;
    }
};

class Character{
public:
    //attributes of class Character
    std::string name;
    int health;
    weapons arsenal [3]; //array of size 3 (number of weapons for each character)
    int weaponCount; //number of weapons added

    //constructor to get called when creating ojects optimus and megatron
    Character(std::string n, int h) : name(n), health(h), weaponCount(0) {}

    bool alive() const{
        return health > 0; //character is alive as long as the health is more than 0
    }

    void takedamage(int damage_amount){
        health -= damage_amount; //health decreases by the damage value till reaching 0
        if (health < 0){
            health = 0;
        }
    }

    void addweapon(const weapons& w){
        if(weaponCount < 3){
            arsenal[weaponCount] = w; //to place weapon in the array arsenal
            weaponCount ++;
        }
    }
void Attack(Character& opponent, int weaponindex){
    if(weaponindex < weaponCount){
        weapons& w = arsenal[weaponindex];
        if (w.attack()) {
            opponent.takedamage(w.damage);
            std::cout << name << " hit " << opponent.name << " with "
                      << w.name << " for " << w.damage << " damage!\n";
        } else {
            std::cout << name << " missed with " << w.name << "!\n";
        }
    }
}
};

//fight function, game logic
void fight(){

    //making an object (optimus) and defining his weapons
    Character optimus("Optimus Prime", 100);
    optimus.addweapon(weapons("Iron rifle", 6, 100));
    optimus.addweapon(weapons("Energon swords", 12, 80));
    optimus.addweapon(weapons("Shoulder canon", 45, 25));

    //making an object (megatron) and definig his weapons
    Character megatron("Megatron", 100);
    megatron.addweapon(weapons("Fusion canon", 9, 90));
    megatron.addweapon(weapons("Fusion sword", 18, 70));
    megatron.addweapon(weapons("Tank mode", 60, 15));

    bool optimusTurn = true;

    //if it is optimus turn, then he will attack megatron, otherwise megatron will attack optimus
    while (optimus.alive() && megatron.alive()) {
        if (optimusTurn) {
            optimus.Attack(megatron, rand() % optimus.weaponCount);
        } else {
            megatron.Attack(optimus, rand() % megatron.weaponCount);
        }
        optimusTurn = !optimusTurn; // flip turn
    }

    if (optimus.alive()) std::cout << "Optimus wins!\n";
    else std::cout << "Megatron wins!\n";

    std::cout<<"Final state:";
    std::cout<< optimus.name <<" health: "<< optimus.health <<"\n";
    std::cout<< megatron.name <<" health: "<< megatron.health <<"\n";
    }
int main(){
    srand(time(0));
    fight(); //calls fight function
    return 0;
}