//
// Created by matthias on 1/7/20.
//

#include <MinionTypes.h>
#include "Minion.h"

#ifndef GBA_SPRITE_ENGINE_PROJECT_BANANAMINION_H
#define GBA_SPRITE_ENGINE_PROJECT_BANANAMINION_H

class BananaMinion: public Minion {
private:

public:
    BananaMinion(int health, int cost, int cooldownTime, std::unique_ptr<Sprite> image, int creationTime) : Minion(BANANA_MINION, health, cost, cooldownTime, std::move(image), creationTime) {}
    void shoot() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BANANAMINION_H