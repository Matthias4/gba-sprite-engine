//
// Created on 11/15/19.
//

#include <libgba-sprite-engine/gba_engine.h>

#include "MainMenu.h"

int main() {

    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    auto mainMenu = new MainMenu(engine);
    engine->setScene(mainMenu);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    for (;;) {
        engine->update();
        engine->delay(1000);
    }
#pragma clang diagnostic pop
}

