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
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <Enemies/ConeheadZombie.h>
#include <Enemies/BasicZombie.h>
#include <Enemies/BucketheadZombie.h>

#include "Level.h"
#include "MainMenu.h"
#include "Level/Minion.h"
#include "Level/BananaMinion.h"
#include "Level/FlowerMinion.h"
#include "Level/Zombie.h"
#include "Level/ZombieWithClothes.h"
#include "Level/ZombieBlind.h"
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

    //waves = { {STANDARD_ZOMBIE} };
}
Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers) : Level(engine) {
    flowers = startingFlowers;
}

Level::Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers, std::vector< std::vector<uint8_t> > waves) : Level(engine, startingFlowers) {
    this->waves = std::move(waves);
}

void Level::createBullet(int gridX, int currentTime, int gridY, int damage, std::unique_ptr<Sprite> sprite) {
    bullets.push_back(std::unique_ptr<Bullet>(new Bullet(gridX * 32, currentTime, gridY, damage, std::move(sprite))));
    engine->updateSpritesInScene();// Reload sprites
}

void Level::updateMinions() {
    int currentTime = engine->getTimer()->getTotalMsecs();

    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            if (grid[x][y] != nullptr) {
                //grid[x][y]->move(x * 32, y * 32 + 32);// Only enable when minions are not placed using the toolbar
                int counter = ((currentTime - grid[x][y]->getCreationTime()) % grid[x][y]->getCooldownTime());
                int cooldownTime = grid[x][y]->getCooldownTime();

                if ((counter >= 0)
                && (counter <= 100)
                && (grid[x][y]->getTotalShot() < (currentTime - grid[x][y]->getCreationTime()) / grid[x][y]->getCooldownTime())) {
                    grid[x][y]->shoot();
                    if (grid[x][y]->getType() == FLOWER_MINION) {
                        addFlower((dynamic_cast<FlowerMinion*>(grid[x][y].get()))->getSunPower());// Dynamic cast, references: http://www.cplusplus.com/forum/general/2710/ and https://stackoverflow.com/questions/26377430/how-to-do-perform-a-dynamic-cast-with-a-unique-ptr
                    } else if (grid[x][y]->getType() == SHOOTER_MINION) {
                        createBullet(x, currentTime, y, dynamic_cast<Shooter*>(grid[x][y].get())->getDamage(), spriteBuilder->buildWithDataOf(*bananaBulletSprite));
                    }
                } else if (counter >= cooldownTime / 2 && counter <= grid[x][y]->getCooldownTime()) {
                    grid[x][y]->stopAnimtation();
                }
            }
        }
    }

    if (selectedMinion != nullptr) {
        selectedMinion->move(selectorX * 32, selectorY * 32 + 32);
    }
}

void Level::updateBullets() {
    //for (int i = 0; i < bullets.size(); i++) {
    for (auto bullet = bullets.begin(); bullet < bullets.end(); bullet++) {
        int currentTime = engine->getTimer()->getTotalMsecs();
        int counter = currentTime - (*bullet)->getCreationTime();
        int newPositionX = (*bullet)->getOriginalPositionX() + counter / BULLET_SPEED_FACTOR;

        (*bullet)->move(newPositionX, (*bullet)->getRow() * 32 + 20);

        int numberOfBullets = bullets.size();

        for (auto & zombie : zombies) {
            if (zombie->getRow() == (*bullet)->getRow()) {
                if (zombie->getPosition() <= newPositionX) {
                    zombie->getHit((*bullet)->getDamage());
                    bullets.erase(bullet);
                }
            }
        }

        if ((*bullet)->getSprite()->isOffScreen()) {
            bullets.erase(bullet);
        }

        if (bullets.size() != numberOfBullets) {
            engine->updateSpritesInScene();// Reload sprites
        }
    }
}

void Level::updateZombies() {
    int currentTime = engine->getTimer()->getTotalMsecs();
    int zombiePosition;

    int numberOfZombies = zombies.size();

    for (auto zombie = zombies.begin(); zombie < zombies.end(); zombie++) {
        if ((*zombie)->getHealth() <= 0) {
            zombies.erase(zombie);
        } else {
            int counter = (currentTime - (*zombie)->getCreationTime());
            if ((*zombie)->getPosition() >= 0) {
                zombiePosition =
                        GBA_SCREEN_WIDTH - ((counter * (*zombie)->getWalkingSpeed()) / (100 * ZOMBIES_SPEED_FACTOR));
                (*zombie)->move(zombiePosition,
                                (*zombie)->getRow() * 32 + 32);
                (*zombie)->setPosition(zombiePosition);
            }
            if ((*zombie)->killedUser()) {
                playerDied = true;
                TextStream::instance().setText(std::string("You died!"), 10, 6);
            }
        }
    }

    if (zombies.size() != numberOfZombies) {
        engine->updateSpritesInScene();// Reload sprites
    }
}

bool Level::nextWave() {
    waveNumber++;
    if (waveNumber >= waves.size()) return false;

    for (auto zombie : waves[waveNumber]) {
        switch (zombie) {
            case STANDARD_ZOMBIE:
                zombies.push_back(std::unique_ptr<Zombie>(new BasicZombie(rand() % LEVEL_GRID_HEIGHT, spriteBuilder->buildWithDataOf(*basicZombieSprite), engine->getTimer()->getTotalMsecs())));
                break;
            case CONEHEAD_ZOMBIE:
                zombies.push_back(std::unique_ptr<Zombie>(new ConeheadZombie(rand() % LEVEL_GRID_HEIGHT, spriteBuilder->buildWithDataOf(*coneheadZombieSprite), engine->getTimer()->getTotalMsecs())));
                break;
            case BUCKETHEAD_ZOMBIE:
                zombies.push_back(std::unique_ptr<Zombie>(new BucketheadZombie(rand() % LEVEL_GRID_HEIGHT, spriteBuilder->buildWithDataOf(*bucketheadZombieSprite), engine->getTimer()->getTotalMsecs())));
                break;
        }
    }

    for (int i = 0; i < zombies.size(); i++) {
        zombies[i]->getSprite()->animate();
    }

    engine->updateSpritesInScene();// Reload sprites

    return true;
}

void Level::updateSelectedMinion() {
    toolbarSprites[selectorX]->animate();
    if (selectorX > 0) {
        toolbarSprites[selectorX - 1]->animateToFrame(0);
        toolbarSprites[selectorX - 1]->stopAnimating();
    }
    if (selectorX <= TOOLBAR_SIZE - 2) {
        toolbarSprites[selectorX + 1]->animateToFrame(0);
        toolbarSprites[selectorX + 1]->stopAnimating();
    }

    engine->updateSpritesInScene();// Reload sprites
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
    returnSprites.push_back(coneheadZombieSprite.get());
    returnSprites.push_back(bucketheadZombieSprite.get());
    returnSprites.push_back(bananaBulletSprite.get());

    // Minions in grid
    for (int x = 0; x < LEVEL_GRID_WIDTH; x++) {
        for (int y = 0; y < LEVEL_GRID_HEIGHT; y++) {
            if (grid[x][y] != nullptr) {
                returnSprites.push_back((*grid[x][y]).getSprite());
            }
        }
    }

    // Minions in toolbar
    for (int i = 0; i < TOOLBAR_SIZE; i++) {
        returnSprites.push_back(toolbarSprites[i].get());
    }

    // To be placed minion
    if (selectedMinion != nullptr) {
        returnSprites.push_back(selectedMinion->getSprite());
    }

    // Bullets
    for (int i = 0; i < bullets.size(); i++) {
        returnSprites.push_back(bullets[i]->getSprite());
    }

    // Zombies
    //for (auto zombie : zombies) {//FIXME: Use iterator
    for (int i = 0; i < zombies.size(); i++) {
        //returnSprites.push_back(zombie->getSprite());
        returnSprites.push_back(zombies[i]->getSprite());
    }

    return returnSprites;
}

void Level::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(BackgroundPal, sizeof(BackgroundPal)));

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite> >(new SpriteBuilder<Sprite>);

    shooterSprite = spriteBuilder->withAnimated(3, 5)
            .withData(MinionTiles, sizeof(MinionTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)// from demo 3
            .buildPtr();

    flowerMinionSprite = spriteBuilder->withAnimated(3, 5)
            .withData(FlowerMinionTiles, sizeof(FlowerMinionTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    basicZombieSprite = spriteBuilder->withAnimated(4, 5)
            .withData(ZombieTiles, sizeof(ZombieTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    coneheadZombieSprite = spriteBuilder->withAnimated(4, 5)
            .withData(ZombieWithClothesTiles, sizeof(ZombieWithClothesTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    bucketheadZombieSprite = spriteBuilder->withAnimated(4, 5)
            .withData(ZombieBlindTiles, sizeof(ZombieBlindTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    bananaBulletSprite = spriteBuilder->withData(BananaTiles, sizeof(BananaTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

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

        if (i == 0) {
            toolbarSprites[i]->animate();// First toolbar item is selected by default and should be animated
        }
    }

    background = std::unique_ptr<Background>(new Background(1, BackgroundTiles, sizeof(BackgroundTiles), Map, sizeof(Map)));
    background->useMapScreenBlock(16);

    engine->getTimer()->start();//TODO: Use this timer to move zombies
}

void Level::tick(u16 keys) {
    if (firstTick) {// First loop: load the current keys pressed, do nothing else
        firstTick = false;
        lastKeys = keys;

        //FIXME: for some reason, this block does not function correctly in load() but does in the first tick
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

            if (i == 0) {
                toolbarSprites[i]->animate();// First toolbar item is selected by default and should be animated
            } else {
                toolbarSprites[i]->stopAnimating();
            }
        }

        engine->updateSpritesInScene();// Reload sprites
        ///////////////////////////////////////////////////////////////////////////

        return;
    }

    if (!(keys & KEY_START) && (lastKeys & KEY_START)) {// START key (enter on emulator), wait until released
        if (!engine->isTransitioning()) {
            //engine->setScene(new MainMenu(engine)); //Eventueel kunnen we hier een boodschap geven 'Are you sure you want to quit the level?' ofzo..
            engine->transitionIntoScene(new MainMenu(engine), new FadeOutScene(3));
        }
        return;
    } else if (playerDied) {// When the player died, do not process the rest if the function (including reading keys other than START)
        lastKeys = keys;

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
            if (selectorX <= LEVEL_GRID_WIDTH - 2) {
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
            switch (toolbar[selectorX]) {
                case SHOOTER_MINION:
                    selectedMinion = std::unique_ptr<Minion>(new Shooter(1, 100, 1000, spriteBuilder->buildWithDataOf(*shooterSprite), engine->getTimer()->getTotalMsecs()));

                    break;
                case FLOWER_MINION:
                    selectedMinion = std::unique_ptr<Minion>(new FlowerMinion(1, 50, 10000, 25, spriteBuilder->buildWithDataOf(*flowerMinionSprite), engine->getTimer()->getTotalMsecs()));

                    break;
            }

            if (flowers >= selectedMinion->getCost()) {
                engine->updateSpritesInScene();// Reload sprites

                selectorX = 0;
                selectorY = 0;
            } else {
                selectedMinion = nullptr;
                plantSelected = false;
            }
        } else {
            if (grid[selectorX][selectorY] == nullptr) {
                if (removeFlower(selectedMinion->getCost())) {
                    grid[selectorX][selectorY] = std::move(selectedMinion);
                    //testboolpleaseremove = true;
                }
            }

            selectedMinion = nullptr;
            engine->updateSpritesInScene();// Reload sprites

            selectorX = 0;
            selectorY = 0;
            updateSelectedMinion();
        }
    } else if ((keys & KEY_B) && ((keys & KEY_B) != (lastKeys & KEY_B))) {
        if (plantSelected) {
            plantSelected = false;
            selectedMinion = nullptr;
            engine->updateSpritesInScene();

            selectorX = 0;
            selectorY = 0;
            updateSelectedMinion();
        }
    }
    lastKeys = keys;

#if SHOWSTART
    if(aantalShowStappen <= (GBA_SCREEN_WIDTH-ZOMBIE_SHOW_PLACE))
    {
        Scroll(false);
        ++aantalShowStappen;
        if(aantalShowStappen > 1) // if this if isn't here, there will be some problems with loading the map.
        {
            return;
        }
    }
    else if(aantalShowStappen <= 2 * (GBA_SCREEN_WIDTH-ZOMBIE_SHOW_PLACE))
    {
        Scroll(true);
        ++aantalShowStappen;
        return;
    }
#endif

    if (zombies.empty()) {// All zombies dead? Start next wave
#if ENABLE_ZOMBIE_START_DELAY
        if (engine->getTimer()->getTotalMsecs() > ZOMBIE_START_DELAY_MS) {
#endif
            if (!nextWave()) {
                TextStream::instance().setText(std::string("You won!"), 10,
                                               6);// In case there is no next wave, the player won
            }
#if ENABLE_ZOMBIE_START_DELAY
        }
#endif
    }

    updateMinions();
    updateBullets();
    updateZombies();

    if (automaticFlowersProduced < (engine->getTimer()->getTotalMsecs() / 10000)) {
        automaticFlowersProduced++;
        addFlower(50);
    }

    TextStream::instance().setText(std::string("Flowers: " + std::to_string(flowers)), 1, 15);
    //TextStream::instance().setText(std::string("Wave: " + std::to_string(waveNumber + 1) + " / Zombies: " + std::to_string(zombies.size())), 3, 1);// @Anouk, meer testen Toppie :D
    //TextStream::instance().setText(std::string("Selector: " + std::to_string(selectorX) + "," + std::to_string(selectorY)), 5, 1);//@Anouk, nog meer testen :o

    //if (testboolpleaseremove) {
    //    TextStream::instance().setText(std::string("Time: " + std::to_string(engine->getTimer()->getTotalMsecs()) + "/" + std::to_string(grid[0][0]->getCreationTime()) + "/" + std::to_string(grid[0][0]->getCooldownTime())), 5, 1);
    //}
}

#if SHOWATSTART
void Level::Scroll(bool toZombies) {
    if (toZombies) {// Scroll to right (to original position)
        for(int ii = 0; ii < zombies.size(); ++ii)
        {
            if(zombies[ii]->getPosition() != GBA_SCREEN_WIDTH)
            {
                if(zombies[ii]->show(false))
                {
                    //Reset the creation time otherwise the zombies will spawn in the middle of the map
                    zombies[ii]->setCreationTime(engine->getTimer()->getTotalMsecs()*1.5);
                }
                zombies[ii]->move(zombies[ii]->getPosition(), zombies[ii]->getRow() * 32 + 32);
            }
        }

    } else {// Scroll to left
        for(int ii = 0; ii < zombies.size(); ++ii)
        {
            if(zombies[ii]->getPosition() != ZOMBIE_SHOW_PLACE)
            {
                zombies[ii]->show(true);
                zombies[ii]->move(zombies[ii]->getPosition(), zombies[ii]->getRow() * 32 + 32);
            }
        }
    }
}
#endif

void Level::addFlower(int numberOfFlowers) {
    flowers += numberOfFlowers;
}

bool Level::removeFlower(int numberOfFlowers) {
    if (flowers - numberOfFlowers < 0) {
        return false;
    }

    flowers -= numberOfFlowers;

    return true;
}