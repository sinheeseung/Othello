#include "controller.h"
#include "model.h"
#include "view.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

Controller::Controller() {
	insModel_ = new Model();
	insView_ = new View();
};

void Controller::ApplicationRun() {
	insView_->showMessage("오델로 판의 크기를 입려해주세요");
	int size = insView_->InputArraySize();
	insModel_->init(size);
	insView_->showArray(insModel_->getArray());
	bool is_end = false;
	do {
		//놓을 수 있는 곳이 있는지 확인
		bool is_possible = is_Continue(true);
		if (is_possible) {
			insView_->showMessage("Player One이 놓을 돌의 위치를 입력하시오: (x y)");
			std::tuple<int, int> result = insView_->inputLocation();
			int x = std::get<0>(result);
			int y = std::get<1>(result);
			insModel_->setArray(x, y, true);
			insView_->showArray(insModel_->getArray());
			Reverse(true); // 뒤집을 돌을 찾아줌
			insView_->showArray(insModel_->getArray());
		}
		else 
			insView_->showMessage("Player One이 놓을 수 있는 위치가 없습니다.");

		is_possible = is_Continue(false);
                if (is_possible) {
                        insView_->showMessage("Player Two가 놓을 돌의 위치를 입력하시오: (x y)");
                        std::tuple<int, int> result = insView_->inputLocation();
                        int x = std::get<0>(result);
                        int y = std::get<1>(result);
                        insModel_->setArray(x, y, false);
                        insView_->showArray(insModel_->getArray());
                        Reverse(false); // 뒤집을 돌을 찾아줌
                        insView_->showArray(insModel_->getArray());
                }
                else
                        insView_->showMessage("Player Two가 놓을 수 있는 위치가 없습니다.");
                
		if ((is_Continue(true) == false and is_Continue(false) == false) or is_End())
		      is_end = true;	

	}while(is_end)
	Score();
}

bool Controller::is_Possible() {
	return true;
}

void Controller::Reverse(bool is_playerone) {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        for (int i=0;i<arr.length();i++){
                for( int j=0;j<arr[i].length();j++){
			if(is_playerone){
				if(arr[i][j] == "B")
					is_Reverse(i,j, is_playerone);
			}else {
				if(arr[i][j] == "W")
					is_Reverse(i,j, is_playerone);
			}
                }
        }
}
void is_Reverse(int i, int j, bool is_playerone){
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
	if(is_playerone) {
		if(i-1>=0 and j-1>=0 and i+1 < arr.length() and j+1 <arr.length()){
			if(arr[i-1][j-1] == "W" and arr[i+1][j+1] == "W")
				insModel_->modifyArray(i,j);
		}
		if(i-1>=0 and i+1 < arr.length()){
                        if(arr[i-1][j] == "W" and arr[i+1][j] == "W")
                                insModel_->modifyArray(i,j);
		}
	        if(j-1>=0 and j+1 <arr.length()){
                        if(arr[i][j-1] == "W" and arr[i][j+1] == "W")
                                insModel_->modifyArray(i,j);
		}
		if(i-1>=0 and j-1>=0 and i+1 < arr.length() and j+1 <arr.length()){
                        if(arr[i-1][j+1] == "W" and arr[i+1][j-1] == "W")
                                insModel_->modifyArray(i,j);
		}
	}
	else {
		if(i-1>=0 and j-1>=0 and i+1 < arr.length() and j+1 <arr.length()){
                        if(arr[i-1][j-1] == "B" and arr[i+1][j+1] == "B")
                                insModel_->modifyArray(i,j);
                }
                if(i-1>=0 and i+1 < arr.length()){
                        if(arr[i-1][j] == "B" and arr[i+1][j] == "B")
                                insModel_->modifyArray(i,j);
                }
                if(j-1>=0 and j+1 <arr.length()){
                        if(arr[i][j-1] == "B" and arr[i][j+1] == "B")
                                insModel_->modifyArray(i,j);
                }
                if(i-1>=0 and j-1>=0 and i+1 < arr.length() and j+1 <arr.length()){
                        if(arr[i-1][j+1] == "B" and arr[i+1][j-1] == "B")
                                insModel_->modifyArray(i,j);
                }
	}
}
bool Controller::is_Continue() {
	return true;
}

bool Controller::is_End() {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int one_count=0;
        int two_count=0;
        for (int i=0;i<arr.length();i++){
                for( int j=0;j<arr[i].length();j++){
                        if(arr[i][j] == "W")
                                one_count += 1;
                        if(arr[i][j] == "B")
                                two_count += 1;
                }
        }
	if (one_count == 0 or two_count == 0)
		return true;
	else
		return false;
}

void Controller::Score() {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
	int one_score=0;
	int two_score=0;
	for (int i=0;i<arr.length();i++){
                for( int j=0;j<arr[i].length();j++){
			if(arr[i][j] == "W")
				one_score += 1;
			if(arr[i][j] == "B")
				two_score += 1;
		}
	}
	insView_->showMessage("Player One의 점수는 ", one_score, "입니다.");
	insView_->showMessage("Player Two의 점수는 ", two_score, "입니다.");
	if (one_score > two_score)
		insView_->showMessage("Player One이 승리했습니다.");
	else
		insView_->showMessage("Player Two가 승리했습니다.");
}
