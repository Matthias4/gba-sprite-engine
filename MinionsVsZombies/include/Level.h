//
// Created by matthias on 11/21/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL_H

#include <libgba-sprite-engine/scene.h>

class Level : public Scene {
private:

public:
    explicit Level(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
