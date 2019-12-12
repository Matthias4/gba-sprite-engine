//
// Created by matthias on 11/21/19.
//

#include <libgba-sprite-engine/scene.h>
#include <Minions/Shooter.h>
#include <Enemies/Zombie.h>
#include "MinionTypes.h"

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL_H

#define LEVEL_GRID_WIDTH 6
#define LEVEL_GRID_HEIGHT 4

#define TOOLBAR_SIZE 2

class Level : public Scene {
private:
    bool firstTick = true;

    uint32_t flowers = 0;// Amount of flowers on start can be entered here

    std::vector< std::vector<uint8_t> > waves;
    int16_t waveNumber = -1;

    std::unique_ptr<Minion> grid[LEVEL_GRID_WIDTH][LEVEL_GRID_HEIGHT];
    void updateMinions();

    std::vector< std::unique_ptr<Zombie> > zombies = std::vector< std::unique_ptr<Zombie> >();
    void updateZombies();
    bool nextWave();

    std::unique_ptr< SpriteBuilder<Sprite> > spriteBuilder;
    std::unique_ptr<Sprite> shooterSprite;
    std::unique_ptr<Sprite> flowerMinionSprite;
    std::unique_ptr<Sprite> basicZombieSprite;

    int toolbar[TOOLBAR_SIZE] = {SHOOTER_MINION, FLOWER_MINION};
    std::unique_ptr<Sprite> toolbarSprites[TOOLBAR_SIZE];
    bool plantSelected = false;
    uint8_t selectorX = 0;
    uint8_t selectorY = 0;
    std::unique_ptr<Minion> selectedMinion = nullptr;
    u16 lastKeys;
    void updateSelectedMinion();

    std::unique_ptr<Background> background;

public:
    explicit Level(const std::shared_ptr<GBAEngine> &engine);
    Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers);
    Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers, std::vector< std::vector<uint8_t> > waves);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;
    void load() override;
    void tick(u16 keys) override;

    void Scroll(bool toZombies);

    inline void addFlower(int numberOfFlowers) {flowers += numberOfFlowers;};
    inline void removeFlower(int numberOfFlowers) {flowers -= numberOfFlowers;};
};

#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
