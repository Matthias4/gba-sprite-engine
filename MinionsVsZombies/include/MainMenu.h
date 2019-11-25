//
// Created by matthias on 11/21/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MAINMENU_H
#define GBA_SPRITE_ENGINE_PROJECT_MAINMENU_H

#include <libgba-sprite-engine/scene.h>

class MainMenu : public Scene {
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> selector;
    std::unique_ptr<Sprite> minion;

public:
    explicit MainMenu(const std::shared_ptr<GBAEngine> &engine);// explicit: no implicit conversion for the engine parameter allowed. ref: https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_MAINMENU_H
