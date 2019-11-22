//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "MainMenu.h"
#include "Level.h"

MainMenu::MainMenu(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> MainMenu::backgrounds() {
    return { };//background.get() };
}

std::vector<Sprite *> MainMenu::sprites() {
    return { };//selector.get() };
}

void MainMenu::load() {
    TextStream::instance().setText(std::string("hello"), 10, 10);
}

void MainMenu::tick(u16 keys) {
    if (keys & KEY_A) {
        // A key pressed, just load the game since our menu only contains the start button ;)
        //engine->setScene(new Level(engine));
    }
}