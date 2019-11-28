//
// Created by matthias on 11/21/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL_H

#include <libgba-sprite-engine/scene.h>

class Level : public Scene {
private:
    uint32_t flowers = 0;// Amount of flowers on start can be entered here
    std::unique_ptr<Sprite> minion;

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
