//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba/tonc_types.h>
#include <vector>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "Level.h"
#include "MainMenu.h"
#include "png/shared.h"
#include "png/minion.h"
#include "png/BananaMinion.h"


Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}
Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers) : Level(engine) {
    flowers = startingFlowers;
}

std::vector<Background *> Level::backgrounds() {
    return {};
}

std::vector<Sprite *> Level::sprites() {
    return {minion.get(), bananaMinion.get()};
}

void Level::load() {

    // Load grass as background

    /*minion = spriteBuilder
            .withData(minion_data, sizeof(minion_data))
            .withSize(SIZE_32_32)
            .withAnimated(3, 10)
            .withLocation(50, 50)
            .buildPtr();*/

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> spriteBuilder;

    minion = spriteBuilder
            .withData(minionTiles, sizeof(minionTiles))
            .withSize(SIZE_32_32)
            .withAnimated(2, 20)
            .withLocation(70, 320)
            .buildPtr();

    bananaMinion = spriteBuilder
            .withData(BananaMinionTiles, sizeof(BananaMinionTiles))
            .withSize(SIZE_32_32)
            .withAnimated(2, 20)
            .withLocation(170, 320)
            .buildPtr();
}

void Level::tick(u16 keys) {
    TextStream::instance().setText(std::string("#Flowers: " + std::to_string(flowers)), 1, 1); //Waarom staat dit hier?
    if (keys & KEY_A) {// A key (x on emulator)
        engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
    }
}

void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right

    } else {// Scroll to left (to original position)

    }
}