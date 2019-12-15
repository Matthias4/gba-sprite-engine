//
// Created by matthias on 11/21/19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MAINMENU_H
#define GBA_SPRITE_ENGINE_PROJECT_MAINMENU_H

#include <libgba-sprite-engine/scene.h>

#define MAINMENU_ENTRIES 2 // Number of menu entries, don't forget to update this or options will become unselectable

class MainMenu : public Scene {
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> minion;

    uint8_t selectedMenuEntry = 0;
    u16 lastKeys = 0;
    bool firstTick = true;

    void updateSelectMinion();

public:
    explicit MainMenu(const std::shared_ptr<GBAEngine> &engine);// explicit: no implicit conversion for the engine parameter allowed. ref: https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;
    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_MAINMENU_H
