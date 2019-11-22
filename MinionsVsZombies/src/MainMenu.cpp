//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "MainMenu.h"
#include "Level.h"

MainMenu::MainMenu(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> MainMenu::sprites() {
    return { };//selector.get() };
}

std::vector<Background *> MainMenu::backgrounds() {
    return { };//background.get() };
}

void MainMenu::load() {
    TextStream::instance().setText(std::string("Minions VS Zombies"), 1, 10);
    TextStream::instance().setText(std::string("Play"), 10, 12);
}

void MainMenu::tick(u16 keys) {
    if (keys & KEY_A) {
        // A key pressed, just load the game since our menu only contains the start button ;)
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new Level(engine), new FadeOutScene(1));
        }
    }
}