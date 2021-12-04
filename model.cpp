#include "Model.h"
#include <vector>
#include <string>
//play one = "ㅁ"
//play two = "*"
Model::Model(int size) {
	bool is_white = true;
        for (int i=0;i<size;i++){
		std::vector<string> arr_1;
                for( int j=0;j<size;j++){
			if((i == size/2 or i == size/2-1) and (j == size/2 or j == size/2-1)) {
				if (is_white){
					arr_1[j] = "ㅁ";
					is_white = false;
				}
				else {
					arr_1[j] = "*";
					is_white = true;
				}
			}
			else
				arr_1[j] = "O";

		}
		arr[i] = arr_1;
	}
};

vector<vector<std::string> Model::getarray() {
	return arr_;
}

void Model::setArray(int x, int y, bool is_playone) {
	if(is_playone)
		arr_[i][j] = "ㅁ";
	else
		arr_[i][j] = "*";
}

void Model::modifyArray(int x, int y) {

}
