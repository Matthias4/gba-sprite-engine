//
// Created by matthias on 11/26/19.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "MainMenu.h"
#include "About.h"
#include "minion_image.h"

About::About(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> About::sprites() {
    return {};
}

std::vector<Background *> About::backgrounds() {
    return {};
}

void About::load() {
    TextStream::instance().setText(std::string("About"), 1, 12);
    TextStream::instance().setText(std::string("Minions Vs Zombies"), 3, 6);
    TextStream::instance().setText(std::string("A game by:"), 6, 9);
    TextStream::instance().setText(std::string("Anouk Michiels"), 8, 7);
    TextStream::instance().setText(std::string("Luc Aarts"), 9, 7);
    TextStream::instance().setText(std::string("Matthias Dekeyser"), 10, 7);
    TextStream::instance().setText(std::string("Press A to return"), 15, 7);
}

void About::tick(u16 keys) {
    if (keys & KEY_A) {// A key (x on emulator)
        engine->setScene(new MainMenu(engine));
    }
}