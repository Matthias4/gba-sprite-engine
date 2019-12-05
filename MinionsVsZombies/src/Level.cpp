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
#include "Level/FlowerMinion.h"
#include "Level/Zombie.h"
#include "Level/Banana.h"
#include "Level/Shared.h"
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
        zombies[i]->move(zombies[i]->getRow() * 32 + 32, zombies[i]->getPosition());
    }
}

bool Level::nextWave() {
    waveNumber++;

    if (waveNumber > waves.size()) return false;

    for (auto zombie : waves[waveNumber]) {
        switch (zombie) {
            case STANDARD_ZOMBIE:
                zombies.push_back(std::unique_ptr<Zombie>(new Zombie(10, 1, 1, 1, 1, spriteBuilder->withLocation(100, 100).buildWithDataOf(*basicZombieSprite.get()))));
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
        //returnSprites.push_back(zombie->getSprite());
        returnSprites.push_back(zombies[i]->getSprite());
    }

    returnSprites.push_back(testZombieSprite.get());

    return returnSprites;
}

void Level::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    //backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    // Load grass as background

    spriteBuilder = std::unique_ptr< SpriteBuilder<Sprite> >(new SpriteBuilder<Sprite>);
    /*std::unique_ptr<Sprite> shooterSprite = spriteBuilder
            .withData(levelMinionTiles, sizeof(levelMinionTiles))
            .withSize(SIZE_32_32)
            .buildPtr();*/

    shooterSprite = spriteBuilder
            ->withData(minionTiles, sizeof(minionTiles))
            .withSize(SIZE_32_32)
            .buildPtr();

    basicZombieSprite = spriteBuilder
            ->withData(zombieTiles, sizeof(zombieTiles))
            .withSize(SIZE_32_32)
            .buildPtr();

    grid[1][1] = new Shooter(1, 1, 1, spriteBuilder->buildWithDataOf(*shooterSprite));
    grid[2][2] = new Shooter(1, 1, 1, spriteBuilder->buildWithDataOf(*shooterSprite)); //Waarom kunnen we die pointer niet maken in de constructor van de Minion?

    testZombieSprite = spriteBuilder->withData(zombieTiles, sizeof(zombieTiles)).withLocation(50, 50).withSize(SIZE_32_32).buildPtr();
}

void Level::tick(u16 keys) {

    if (keys & KEY_A) {// A key (x on emulator) //
        engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
        return;
    }

    TextStream::instance().setText(std::string("Flowers: " + std::to_string(flowers)), 1, 1);
    TextStream::instance().setText(std::string("Wave: " + std::to_string(waveNumber + 1) + " / Zombies: " + std::to_string(zombies.size())), 3, 1);// @Anouk, meer testen Toppie :D


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