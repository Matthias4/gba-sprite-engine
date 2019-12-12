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

#define ZombieShowPlace (GBA_SCREEN_WIDTH / 2)

int aantalShowStappen = 0; // the number of steps all the zombies step when the game starts for the first time

Level::Level(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            grid[x][y] = nullptr;
        }
    }

    //waves = { {STANDARD_ZOMBIE} };
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
                grid[x][y]->move(x * 32, y * 32 + 32);//FIXME: Minions are moved EVERY tick, should only be moved once...
            }
        }
    }

    if (selectedMinion != nullptr) {
        selectedMinion->move(selectorX * 32, selectorY * 32 + 32);
    }
}

void Level::updateZombies() {
    //for (auto zombie : zombies) {//FIXME: Use iterator
    for (int i = 0; i < zombies.size(); i++) {
        zombies[i]->walk();
        zombies[i]->move(zombies[i]->getPosition(), zombies[i]->getRow() * 32 + 32);
        if(zombies[i]->getPosition() == 0)
        {
            //--Leven;
        }
    }
}

bool Level::nextWave() {
    waveNumber++;
    if (waveNumber >= waves.size()) return false;

    for (auto zombie : waves[waveNumber]) {
        switch (zombie) {
            case STANDARD_ZOMBIE:
                zombies.push_back(std::unique_ptr<Zombie>(new Zombie(10, 1, 1, rand() % LEVEL_GRID_HEIGHT, spriteBuilder->buildWithDataOf(*basicZombieSprite))));
                break;
            case CONEHEAD_ZOMBIE:
                //TODO: Create conehead zombie class and use here
                break;
            case BUCKETHEAD_ZOMBIE:
                //TODO: Create buckethead zombie class and use here
                break;
        }
    }

    engine->updateSpritesInScene();// Reload sprites

    return true;
}

void Level::updateSelectedMinion() {
    toolbarSprites[selectorX]->animate();
    if (selectorX > 0) {
        toolbarSprites[selectorX - 1]->stopAnimating();
    }
    if (selectorX <= TOOLBAR_SIZE - 2) {
        toolbarSprites[selectorX + 1]->stopAnimating();
    }

    engine->updateSpritesInScene();// Reload sprites  //TODO: test me
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

    if (selectedMinion != nullptr) {
        returnSprites.push_back(selectedMinion->getSprite());
    }

    //for (auto zombie : zombies) {//FIXME: Use iterator
    for (int i = 0; i < zombies.size(); i++) {
        //returnSprites.push_back(zombie->getSprite());
        returnSprites.push_back(zombies[i]->getSprite());
    }

    for (int i = 0; i < TOOLBAR_SIZE; i++) {
        returnSprites.push_back(toolbarSprites[i].get());
    }

    return returnSprites;
}

void Level::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(BackgroundPal, sizeof(BackgroundPal)));

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite> >(new SpriteBuilder<Sprite>);

    shooterSprite = spriteBuilder->withAnimated(3, 2)
            .withData(MinionTiles, sizeof(MinionTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)// from demo 3
            .buildPtr();

    flowerMinionSprite = spriteBuilder->withAnimated(3, 1)
            .withData(FlowerMinionTiles, sizeof(FlowerMinionTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    basicZombieSprite = spriteBuilder->withAnimated(4, 2)
            .withData(ZombieTiles, sizeof(ZombieTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    grid[1][1] = std::unique_ptr<Minion>(new Shooter(1, 1, 1, spriteBuilder->buildWithDataOf(*shooterSprite)));
    grid[2][2] = std::unique_ptr<Minion>(new FlowerMinion(1, 1, 1, spriteBuilder->buildWithDataOf(
            *flowerMinionSprite))); //Waarom kunnen we die pointer niet maken in de constructor van de Minion? spriteBuilder en flowerMinionSprite kan je daar niet aan :(

    for (int i = 0; i < TOOLBAR_SIZE; i++) {//TODO: Optimize this block
        int x = 32;
        int y = 0;
        switch (toolbar[i]) {
            case SHOOTER_MINION:
                toolbarSprites[i] = spriteBuilder->withLocation(i * x, y).buildWithDataOf(*shooterSprite);
                break;
            case FLOWER_MINION:
                toolbarSprites[i] = spriteBuilder->withLocation(i * x, y).buildWithDataOf(*flowerMinionSprite);
                break;
        }
    }

    //zombies.push_back(std::unique_ptr<Zombie>(new Zombie(10, 1, 1, 1, spriteBuilder->buildWithDataOf(*basicZombieSprite))));

    //testZombieSprite = spriteBuilder->withData(ZombieTiles, sizeof(ZombieTiles)).withLocation(50, 50).withSize(SIZE_32_32).buildPtr();

    background = std::unique_ptr<Background>(new Background(1, BackgroundTiles, sizeof(BackgroundTiles), Map, sizeof(Map)));
    background->useMapScreenBlock(16);

    engine->getTimer()->start();//TODO: Use this timer to move zombies
}

void Level::tick(u16 keys) {
    if (firstTick) {
        firstTick = false;
        lastKeys = keys;

        return;
    }

    if (!(keys & KEY_START) && (lastKeys & KEY_START)) {// Enter key, wait until released
        engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
        return;
    } else if ((keys & KEY_LEFT) && ((keys & KEY_LEFT) != (lastKeys & KEY_LEFT))) {
        if (selectorX > 0) {
            selectorX--;
        }

        if (plantSelected) {

        } else {
            updateSelectedMinion();
        }
    } else if ((keys & KEY_RIGHT) && ((keys & KEY_RIGHT) != (lastKeys & KEY_RIGHT))) {
        if (plantSelected) {
            if (selectorX <= LEVEL_GRID_WIDTH - 1) {
                selectorX++;
            }
        } else {
            if (selectorX <= TOOLBAR_SIZE - 2) {
                selectorX++;
                updateSelectedMinion();
            }
        }
    } else if ((keys & KEY_UP) && ((keys & KEY_UP) != (lastKeys & KEY_UP))) {
        if (plantSelected) {
            if (selectorY > 0) {
                selectorY--;
            }
        }
    } else if ((keys & KEY_DOWN) && ((keys & KEY_DOWN) != (lastKeys & KEY_DOWN))) {
        if (plantSelected) {
            if (selectorY <= LEVEL_GRID_HEIGHT - 2) {
                selectorY++;
            }
        }
    } else if ((keys & KEY_A) && ((keys & KEY_A) != (lastKeys & KEY_A))) {// A key (x on emulator) //
        plantSelected = !plantSelected;
        if (plantSelected) {
            //TODO: check if player has sufficient sun

            switch (toolbar[selectorX]) {
                case SHOOTER_MINION:
                    selectedMinion = std::unique_ptr<Minion>(new Shooter(1, 1, 1, spriteBuilder->buildWithDataOf(*shooterSprite)));

                    break;
                case FLOWER_MINION:
                    selectedMinion = std::unique_ptr<Minion>(new FlowerMinion(1, 1, 1, spriteBuilder->buildWithDataOf(*flowerMinionSprite)));

                    break;
            }

            engine->updateSpritesInScene();// Reload sprites

            selectorX = 0;
            selectorY = 0;
        } else {
            //TODO: put plant down
            if (grid[selectorX][selectorY] == nullptr) {
                grid[selectorX][selectorY] = std::move(selectedMinion);
                //TODO: subtract sun
            }

            selectedMinion = nullptr;

            selectorX = 0;
            selectorY = 0;
        }
    }
    lastKeys = keys;

    if((aantalShowStappen <= (GBA_SCREEN_WIDTH-ZombieShowPlace)) && (!firstTick))
    {
        Scroll(false);
        ++aantalShowStappen;
        if(aantalShowStappen > 1) // if this if isn't here, there will be some problems with loading the map.
        {
            return;
        }
    }
    else if(aantalShowStappen <= 2 * (GBA_SCREEN_WIDTH-ZombieShowPlace))
    {
        Scroll(true);
        ++aantalShowStappen;
        return;
    }

    if (zombies.empty()) {// All zombies dead? Start next wave
        if (!nextWave()) {
            TextStream::instance().setText(std::string("You won!"), 10, 6);
        }
    }

    updateMinions();
    updateZombies();

    TextStream::instance().setText(std::string("Flowers: " + std::to_string(flowers)), 1, 1);
    TextStream::instance().setText(std::string("Wave: " + std::to_string(waveNumber + 1) + " / Zombies: " + std::to_string(zombies.size())), 3, 1);// @Anouk, meer testen Toppie :D
    TextStream::instance().setText(std::string("Selector: " + std::to_string(selectorX) + "," + std::to_string(selectorY)), 5, 1);//@Anouk, nog meer testen :o
}

void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right (to original position)
    {
        for(int ii = 0; ii < zombies.size(); ++ii)
        {
            if(zombies[ii]->getPosition() != GBA_SCREEN_WIDTH)
            {
                zombies[ii]->show(false);
                zombies[ii]->move(zombies[ii]->getPosition(), zombies[ii]->getRow() * 32 + 32);
            }
        }
    }

    } else {// Scroll to left
        for(int ii = 0; ii < zombies.size(); ++ii)
        {
            if(zombies[ii]->getPosition() != ZombieShowPlace)
            {
                zombies[ii]->show(true);
                zombies[ii]->move(zombies[ii]->getPosition(), zombies[ii]->getRow() * 32 + 32);
            }
        }
    }
}