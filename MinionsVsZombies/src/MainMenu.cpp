//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "MainMenu.h"
#include "Level.h"
#include "minion_image.h"

MainMenu::MainMenu(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> MainMenu::sprites() {
    return { minion.get() };//selector.get() };
}

std::vector<Background *> MainMenu::backgrounds() {
    return { };//background.get() };
}

void MainMenu::load() {
    //foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> spriteBuilder;

    minion = spriteBuilder
            //.withData(minionTiles, sizeof(minionTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 3)
            .withLocation(50, 50)
            .buildPtr();

    TextStream::instance().setText(std::string("Minions VS Zombies"), 1, 8);
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