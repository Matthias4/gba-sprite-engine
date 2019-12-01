//
// Created by matthias on 11/21/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL_H

#include <libgba-sprite-engine/scene.h>
#include <Minions/Shooter.h>

#define LEVEL_GRID_WIDTH 6
#define LEVEL_GRID_HEIGHT 4

class Level : public Scene {
private:
    uint32_t flowers = 0;// Amount of flowers on start can be entered here
    /* tests */
    std::unique_ptr<Sprite> minion;
    std::unique_ptr<Sprite> bananaMinion;
    std::unique_ptr<Sprite> zombie;
    /* ///// */

    Minion* grid[LEVEL_GRID_WIDTH][LEVEL_GRID_HEIGHT];
    void updateMinions();

public:
    explicit Level(const std::shared_ptr<GBAEngine> &engine);
    Level(const std::shared_ptr<GBAEngine> &engine, uint32_t startingFlowers);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;
    void load() override;
    void tick(u16 keys) override;

    void Scroll(bool toZombies);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
