//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/gba/tonc_types.h>
#include <utility>
#include <vector>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <Minions/Shooter.h>
#include <Minions/FlowerMinion.h>

#include "Level.h"
#include "MainMenu.h"
#include "Level/Minion.h"
#include "Level/BananaMinion.h"
#include "Level/FlowerMinion.h"
#include "Level/Zombie.h"
#include "Level/Banana.h"
#include "Level/Shared.h"
#include "ZombieTypes.h"

// Includes for the background
#include "Level/Background.h"
#include "Level/Map.h"


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
    this->waves = std::move(waves);
}

void Level::updateMinions() {
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            if (grid[x][y] != nullptr) {
                grid[x][y]->move(x * 32, y * 32 + 12);//FIXME: Minions are moved EVERY tick, should only be moved once...
            }
        }
    }
}

void Level::updateZombies() {
    //for (auto zombie : zombies) {//FIXME: Use iterator
    for (int i = 0; i < zombies.size(); i++) {
        //zombies[i]->walk();
        //zombie.move(0, 0);//zombie.getRow() * 32 + 32, 50);//, zombie.getPosition());
        zombies[i]->move(zombies[i]->getPosition(), zombies[i]->getRow() * 32 + 12);
    }
}

bool Level::nextWave() {
    waveNumber++;
    if (waveNumber >= waves.size()) return false;

    for (auto zombie : waves[waveNumber]) {
        switch (zombie) {
            case STANDARD_ZOMBIE:
                zombies.push_back(std::unique_ptr<Zombie>(new Zombie(10, 1, 1, 1, spriteBuilder->withLocation(100, 100).buildWithDataOf(*basicZombieSprite))));
                break;
            case CONEHEAD_ZOMBIE:
                //TODO: Create conehead zombie class and use here
                break;
            case BUCKETHEAD_ZOMBIE:
                //TODO: Create buckethead zombie class and use here
                break;
        }
    }

    engine->updateSpritesInScene();

    return true;
}

std::vector<Background *> Level::backgrounds() {
    return { background.get() };
}

std::vector<Sprite *> Level::sprites() {
    std::vector<Sprite *> returnSprites;

    // Sprite templates
    returnSprites.push_back(shooterSprite.get());
    returnSprites.push_back(flowerMinionSprite.get());
    returnSprites.push_back(basicZombieSprite.get());

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

    for (int i = 0; i < TOOLBAR_SIZE; i++) {
        returnSprites.push_back(toolbar[i].get());
    }

    //TextStream::instance().setText(std::to_string((unsigned int) zombies[0]->getSprite()), 5, 1);// Sprite address

    //returnSprites.push_back(testZombieSprite.get());

    return returnSprites;
}

void Level::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(BackgroundPal, sizeof(BackgroundPal)));

    // Load grass as background

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite> >(new SpriteBuilder<Sprite>);
    /*std::unique_ptr<Sprite> shooterSprite = spriteBuilder
            .withData(levelMinionTiles, sizeof(levelMinionTiles))
            .withSize(SIZE_32_32)
            .buildPtr();*/

    shooterSprite = spriteBuilder->withData(MinionTiles, sizeof(MinionTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)// from demo 3
            .buildPtr();

    flowerMinionSprite = spriteBuilder->withData(FlowerMinionTiles, sizeof(FlowerMinionTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    basicZombieSprite = spriteBuilder->withData(ZombieTiles, sizeof(ZombieTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    grid[1][1] = std::unique_ptr<Minion>(new Shooter(1, 1, 1, spriteBuilder->buildWithDataOf(*shooterSprite)));
    grid[2][2] = std::unique_ptr<Minion>(new FlowerMinion(1, 1, 1, spriteBuilder->buildWithDataOf(
            *flowerMinionSprite))); //Waarom kunnen we die pointer niet maken in de constructor van de Minion?

    for (int i = 0; i < TOOLBAR_SIZE; i++) {//TODO: Optimize this block
        int x = 32;
        int y = -10;
        switch (i) {
            case 0:
                toolbar[i] = spriteBuilder->withLocation(i * x, y).buildWithDataOf(*shooterSprite);
                break;
            case 1:
                toolbar[i] = spriteBuilder->withLocation(i * x, y).buildWithDataOf(*flowerMinionSprite);
                break;
        }
    }

    //zombies.push_back(std::unique_ptr<Zombie>(new Zombie(10, 1, 1, 1, spriteBuilder->buildWithDataOf(*basicZombieSprite))));

    //testZombieSprite = spriteBuilder->withData(ZombieTiles, sizeof(ZombieTiles)).withLocation(50, 50).withSize(SIZE_32_32).buildPtr();

    background = std::unique_ptr<Background>(new Background(1, BackgroundTiles, sizeof(BackgroundTiles), map, sizeof(map)));
    background.get()->useMapScreenBlock(16);

    engine->getTimer()->start();
}

void Level::tick(u16 keys) {

    if (keys & KEY_A) {// A key (x on emulator) //
        engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
        return;
    }

    TextStream::instance().setText(std::string("Flowers: " + std::to_string(flowers)), 1, 1);
    TextStream::instance().setText(std::string("Wave: " + std::to_string(waveNumber + 1) + " / Zombies: " + std::to_string(zombies.size())), 3, 1);// @Anouk, meer testen Toppie :D

    if (zombies.empty()) {// All zombies dead? Start next wave
        if (!nextWave()) {
            TextStream::instance().setText(std::string("You won!"), 10, 6);
        }
    }

    //TextStream::instance().setText(std::to_string((int) zombies[0]->getSprite()), 5, 1);//print address

    updateMinions();
    updateZombies();
}

void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right

    } else {// Scroll to left (to original position)

    }
}