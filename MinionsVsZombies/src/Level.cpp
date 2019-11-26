//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba/tonc_types.h>
#include <vector>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "Level.h"

Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}
Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers) : Level(engine) {
    flowers = startingFlowers;
}

std::vector<Background *> Level::backgrounds() {
    return {};
}

std::vector<Sprite *> Level::sprites() {
    return {};
}

void Level::load() {
    /*minion = spriteBuilder
            .withData(minion_data, sizeof(minion_data))
            .withSize(SIZE_32_32)
            .withAnimated(3, 10)
            .withLocation(50, 50)
            .buildPtr();*/
}

void Level::tick(u16 keys) {
    TextStream::instance().setText(std::string("#Flowers: " + std::to_string(flowers)), 1, 1);
}

void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right

    } else {// Scroll to left (to original position)

    }
}