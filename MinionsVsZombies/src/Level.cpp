//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba/tonc_types.h>
#include <vector>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "Level.h"

Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> Level::backgrounds() {
    return {};
}

std::vector<Sprite *> Level::sprites() {
    return {};
}

void Level::load() {
    TextStream::instance().setText(std::string("lvl 1"), 1, 1);
}

void Level::tick(u16 keys) {

}