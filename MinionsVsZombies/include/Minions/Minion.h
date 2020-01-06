//
// Created by michi on 26/11/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MINION_H
#define GBA_SPRITE_ENGINE_PROJECT_MINION_H

#include <libgba-sprite-engine/scene.h>

class Minion {
private:
    int type;
    int health;
    int cost;
    int cooldownTime;
    int creationTime;

    std::unique_ptr<Sprite> image;

protected:
    int totalShot = 0;

public:
    Minion(int type, int health, int cost, int cooldownTime, std::unique_ptr<Sprite> image, int creationTime);

    int getType() { return type; }
    int getHealth();
    int getCost();
    int getCooldownTime();
    int getCreationTime() { return creationTime; }

    void setHealth(int damage);

    virtual void shoot() = 0; //FIXME: moeten we deze functie wegdoen? En gewoon bij shooter zetten?
                                // Zoja, waar moeten we dan virtual zetten? Moet we een functie getPlanted() hebben ofzo waar we
                                // virtual bij kunnen zetten?
    int getTotalShot();

    Sprite *getSprite();
    void move(int x, int y);
    void stopAnimtation();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_MINION_H
