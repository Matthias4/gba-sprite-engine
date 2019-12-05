//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "Level.h"
#include "About.h"
#include "minion_image.h"
#include "MainMenu.h"
#include "ZombieTypes.h"

MainMenu::MainMenu(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

void MainMenu::updateSelectMinion() {
    minion->moveTo(70, 320 + selectedMenuEntry * 32);
}

std::vector<Sprite *> MainMenu::sprites() {
    return { minion.get() };
}

std::vector<Background *> MainMenu::backgrounds() {
    return { };//background.get() };
}

void MainMenu::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(minion_palette, sizeof(minion_palette)));
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> spriteBuilder;

    minion = spriteBuilder
            .withData(minion_data, sizeof(minion_data))
            .withSize(SIZE_32_32)
            .withAnimated(2, 20)
            .withLocation(70, 320)
            .buildPtr();

    //TextStream::instance().setFontColor(PaletteManager::color(31, 0, 0));// Could be useful, but does not work ;)
    TextStream::instance().setText(std::string("Minions VS Zombies"), 1, 6);
    TextStream::instance().setText(std::string("Play"), 10, 13);
    TextStream::instance().setText(std::string("About"), 14, 13);
}

void MainMenu::tick(u16 keys) {
    //TextStream::instance().setText(std::string("hi"), 1, 1);
    if (keys & KEY_START) {// ENTER key
        if (selectedMenuEntry == 0) {
            if (!engine->isTransitioning()) {
                //engine->transitionIntoScene(new Level(engine, 100/*, { {STANDARD_ZOMBIE}, {STANDARD_ZOMBIE, STANDARD_ZOMBIE} }*/), new FadeOutScene(3));
                engine->setScene(new Level(engine, 100));
            }
            //engine->setScene(new Level(engine));
        } else if (selectedMenuEntry == 1) {
            engine->setScene(new About(engine));
        }
    } else if ((keys & KEY_DOWN) && !(previousKeys & KEY_DOWN)) {
        if (selectedMenuEntry + 1 < MAINMENU_ENTRIES) {
            selectedMenuEntry++;

            updateSelectMinion();
        }
    } else if ((keys & KEY_UP) && !(previousKeys & KEY_UP)) {
        if (selectedMenuEntry  > 0) {
            selectedMenuEntry--;

            updateSelectMinion();
        }
    }

    previousKeys = keys;
}