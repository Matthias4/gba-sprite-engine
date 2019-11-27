//
// Created by michi on 26/11/2019.
//

#include "Enemies/Zombie.h"

int Zombie::getWalkingSpeed() {
    return walkingSpeed;
}

int Zombie::getDamage() {
    return damage;
}

int Zombie::getRow() {
    return row;
}

int Zombie::getPosition() {
    return position;
}

void Zombie::walk() {
                        // Ging level ook de locatie van de zombies bijhouden? Ik dacht alleen van de minions. Het was mijn veronderstelling dat level gewoon een lijst van zombies heeft
                        // en dat de zombies zelf weten waar ze zijn en zelf vooruitwandelen enzo. Als we met een locatiearray voor de zombies zouden werken
                        //dan moeten ze hun eigen positie en row ook niet bijhouden wel?

                        //Juist... Zombies zitten inderdaad niet in die array
    // wandel wandel
    //position--; ofzo
}
