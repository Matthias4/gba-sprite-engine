//
// Created by matthias on 11/26/19.
//

// Just a useless class to add a second entry on out main menu :)

#ifndef GBA_SPRITE_ENGINE_PROJECT_ABOUT_H
#define GBA_SPRITE_ENGINE_PROJECT_ABOUT_H

#include <libgba-sprite-engine/scene.h>

class About : public Scene {
private:

public:
    explicit About(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;
    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_ABOUT_H
