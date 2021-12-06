#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "view.h"
View::View(void) {}

void View::showMessage(std::string text) {
        std::cout << text << std::endl;
}

int View::InputArraySize() {
        int size;
        std::cin >> size;
        return size;
}

void View::showArray(std::vector<std::vector<std::string>> arr) {
       for (int i = 0; i < arr.size(); i++) {
               for (int j = 0; j < arr[i].size(); j++) {
                       std::cout << arr[i][j] << " ";
                }
                std::cout << std::endl;
       }
}

std::tuple<int, int> View::inputLocation() {
        int x, y;
        std::cin >> x >> y;
        return {x, y};
}
