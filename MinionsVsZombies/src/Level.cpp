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
#include <Minions/Shooter.h>

#include "Level.h"
#include "MainMenu.h"
#include "Level/LevelFGPalette.h"
#include "Level/Minion.h"
#include "Level/BananaMinion.h"


Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            grid[x][y] = nullptr;
        }
    }
}
Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers) : Level(engine) {
    flowers = startingFlowers;
}

void Level::updateMinions() {
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            if (grid[x][y] != nullptr) {
                grid[x][y]->move(x * 32, y * 32 + 32);
            }
        }
    }
}

std::vector<Background *> Level::backgrounds() {
    return {};
}

std::vector<Sprite *> Level::sprites() {
    std::vector<Sprite *> returnSprites;

    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            if (grid[x][y] != nullptr) {
                returnSprites.push_back((*grid[x][y]).getSprite());
            }
        }
    }

    return returnSprites;
}

void Level::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(levelFGPalette, sizeof(levelFGPalette)));
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    // Load grass as background

    SpriteBuilder<Sprite> spriteBuilder;

    grid[1][1] = new Shooter(1, 1, 1, spriteBuilder
            .withData(levelMinionTiles, sizeof(levelMinionTiles))
            .withSize(SIZE_32_32)
            .buildPtr());
    grid[2][2] = new Shooter(1, 1, 1, spriteBuilder
            .withData(levelMinionTiles, sizeof(levelMinionTiles))
            .withSize(SIZE_32_32)
            .buildPtr());
}

void Level::tick(u16 keys) {
    TextStream::instance().setText(std::string("#Flowers: " + std::to_string(flowers)), 1, 1); //Waarom staat dit hier? Just a test :)
    if (keys & KEY_A) {// A key (x on emulator)
        engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
    }

    updateMinions();
}

void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right

    } else {// Scroll to left (to original position)

    }
}