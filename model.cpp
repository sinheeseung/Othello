/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#include <vector>
#include <iostream>
#include <string>
#include "model.h"
// play one = "W"
// play two = "B"
Model::Model(void) {}

void Model::init(int size) {
        size_ = size;
        bool is_white = true;
        for (int i = 0; i < size; i++) {
               std::vector<std::string> arr_1;
               for (int j = 0; j < size; j++) {
                       arr_1.push_back("O");
               }
               arr_.push_back(arr_1);
        }
        arr_[size/2 - 1][size/2 - 1] = "W";
        arr_[size/2][size/2] = "W";
        arr_[size/2][size/2 - 1] = "B";
        arr_[size/2 - 1][size/2] = "B";
}

int Model::getSize() {
        return size_;
}
std::vector<std::vector<std::string>> Model::getArray() {
        return arr_;
}

void Model::setArray(int y, int x, bool is_playone) {
        if (is_playone)
                arr_[y][x] = "W";
        else
                arr_[y][x] = "B";
}

void Model::modifyArray(int y, int x) {
    if (arr_[y][x] == "W") {
               arr_[y][x] = "B";
               return;
       }
       if (arr_[y][x] == "B") {
               arr_[y][x] = "W";
               return;
       }
}
