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
#include "Level/Zombie.h"
#include "ZombieTypes.h"


Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            grid[x][y] = nullptr;
        }
    }

    waves = { {STANDARD_ZOMBIE} };
}
Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers) : Level(engine) {
    flowers = startingFlowers;
}

Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers, std::vector< std::vector<uint8_t> > waves) : Level(engine, startingFlowers) {
    this->waves = waves;
}

void Level::updateMinions() {
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            if (grid[x][y] != nullptr) {
                grid[x][y]->move(x * 32, y * 32 + 32);//FIXME: Minions are moved EVERY tick, should only be moved once...
            }
        }
    }
}

void Level::updateZombies() {
    //for (auto zombie : zombies) {//FIXME: Use iterator
    for (int i = 0; i < zombies.size(); i++) {
        //zombie.move(0, 0);//zombie.getRow() * 32 + 32, 50);//, zombie.getPosition());
        zombies[i].move(zombies[i].getRow() * 32 + 32, zombies[i].getPosition());
    }
}

bool Level::nextWave() {
    waveNumber++;

    if (waveNumber > waves.size()) return false;

    SpriteBuilder<Sprite> spriteBuilder;

    for (auto zombie : waves[waveNumber]) {
        switch (zombie) {
            case STANDARD_ZOMBIE:
                zombies.push_back(Zombie(10, 1, 1, 1, 1, spriteBuilder.withData(levelZombieTiles, sizeof(levelZombieTiles)).withSize(SIZE_32_32).buildPtr()));
                break;
            case CONEHEAD_ZOMBIE:
                //TODO: Create conehead zombie class and use here
                break;
            case BUCKETHEAD_ZOMBIE:
                //TODO: Create buckethead zombie class and use here
                break;
        }
    }

    return true;
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

    //for (auto zombie : zombies) {//FIXME: Use iterator
    for (int i = 0; i < zombies.size(); i++) {
        //returnSprites.push_back(zombie.getSprite());
        returnSprites.push_back(zombies[i].getSprite());
    }

    return returnSprites;
}

void Level::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(levelFGPalette, sizeof(levelFGPalette)));
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    // Load grass as background

    SpriteBuilder<Sprite> spriteBuilder;
    /*std::unique_ptr<Sprite> shooterSprite = spriteBuilder
            .withData(levelMinionTiles, sizeof(levelMinionTiles))
            .withSize(SIZE_32_32)
            .buildPtr();*/

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
    TextStream::instance().setText(std::string("#Flowers: " + std::to_string(flowers)), 1, 1); //Waarom staat dit hier? Just a test :) Okidoki :)
    if (keys & KEY_A) {// A key (x on emulator) //FIXME: Als je teruggaat, is er geen selectieminion meer
        engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
    }

    if (zombies.empty()) {// All zombies dead? Start next wave
        nextWave();
    }

    updateMinions();
    updateZombies();
}

void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right

    } else {// Scroll to left (to original position)

    }
}