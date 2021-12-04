#include "view.h"
#include <iostream>
#include <vector>
#include <string>
view::view(void) {};

void view::showMessage(std::string text) {
        std::cout << text << std::endl;
}

int view::InputArraySize() {
        int size;
        std::cin >> size;
        return size;
}

void view::showArray(vector<vector<std::string>> arr) {
	for (int i=0;i<arr.size(); i++){
		for(int j=0;j<arr[i].size(); j++){
			std::cout << arr[i][j] << " ";
		}
		std::cout << endl;
	}
}

std::tuple<int, int> inputLocation() {
        int x, y;
        std::cin >> x >> y;
        return {x,y};
}
