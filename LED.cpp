//
// Created by twodcube on 2/2/19.
//

#include <SDL2/SDL.h>
#include <iostream>
#include "LED.h"

void LED::init() {
    this->LEDs = *new std::vector<std::vector<int>>;
    for (int i = 0; i < 8; i++) {
        std::vector<int> props;
        props.push_back(0);
        props.push_back(0);
        props.push_back(0);
        props.push_back(0);
        this->LEDs.push_back(props);
    }
}

void LED::change(int num, int red, int green, int blue, int alpha) {
    this->LEDs.at(num).at(0) = red;
    this->LEDs.at(num).at(1) = green;
    this->LEDs.at(num).at(2) = blue;
    this->LEDs.at(num).at(3) = alpha;
}

void LED::render(SDL_Renderer * rend) {
    for (int i = 0; i < this->LEDs.size(); i++) {
        SDL_SetRenderDrawColor(rend, this->LEDs.at(i).at(0), this->LEDs.at(i).at(1), this->LEDs.at(i).at(2), this->LEDs.at(i).at(3));
        SDL_Rect rect;
        rect.x = 100*i;
        rect.y = 0;
        rect.w = 100;
        rect.h = 100;
        SDL_RenderFillRect(rend, &rect);
    }
}
