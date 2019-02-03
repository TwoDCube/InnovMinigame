//
// Created by twodcube on 2/2/19.
//

#ifndef MINIGAME_LED_H
#define MINIGAME_LED_H

#include <vector>


class LED {
public:
    void change(int num, int red, int green, int blue, int alpha);
    void render(SDL_Renderer * renderer);
    void init();

private:
    std::vector<std::vector<int>> LEDs;
};


#endif //MINIGAME_LED_H
