#include "view.h"
#include <iostream>

view::view(void) {};

void view::showMessage(std::string text) {
        std::cout << text << std::endl;
}

int view::InputArraySize() {
        int size;
        std::cin >> size;
        return size;
}

void view::showArray() {
}

std::tuple<int, int> inputLocation() {
        int x, y;
        std::cin >> x >> y;
        return {x,y};
}
