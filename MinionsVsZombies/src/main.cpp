//
// Created on 11/15/19.
//

#include <libgba-sprite-engine/gba_engine.h>

int main() {

    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    for (;;) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}

