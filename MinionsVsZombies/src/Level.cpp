//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba/tonc_types.h>
#include <vector>
#include <libgba-sprite-engine/sprites/sprite.h>

#include "Level.h"

Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> Level::backgrounds() {
    return {};
}

std::vector<Sprite *> Level::sprites() {
    return {};
}

void Level::load() {

}

void Level::tick(u16 keys) {

}