#include "controller.h"
#include "model.h"
#include "view.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

void ApplicationRun(); // game main flow
bool is_Possible(); // Player가 선택한 위치에 돌을 놓을 수 있는지 확인
void Reverse(bool is_playerone); // 돌을 뒤집는 함수
bool is_Continue(); // Player가 돌을 놓을 수 있는곳이 있는 지확인
bool is_End(); //종료조건 확인(판에 하나의 돌만 있는 경우)
void Score(); //경기가 종료된 후 점수 계산
void is_Reverse(int i, int j, bool is_playerone);

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
		bool put = false;
		if (is_possible) {
			do{
				insView_->showMessage("");
				insView_->showMessage("Player One이 놓을 돌의 위치를 입력하시오: (x y)");
				std::tuple<int, int> result = insView_->inputLocation();
				int x = std::get<0>(result) - 1;
				int y = std::get<1>(result) - 1;
				if (x >= 0 and x < size and y >= 0 and y < size) {
					bool is_locatable = is_Possible(x, y, true);
					if (is_locatable) {
						insModel_->setArray(x, y, true);
						//insView_->showArray(insModel_->getArray());
						put = true;
					}
					else {
						insView_->showMessage("자신과 상대편 돌 사이에만 돌을 놓을 수 있습니다");
					}
				}
				else {
					put = false;
					insView_->showMessage("잘못된 범위의 값을 입력하였습니다.");
					insView_->showMessage("1~"+std::to_string(size)+" 사이의 값을 입력해주세요.");
				}
			} while(!put);
			Reverse(true); // 뒤집을 돌을 찾아줌
			insView_->showArray(insModel_->getArray());
		}
		else 
			insView_->showMessage("Player One이 놓을 수 있는 위치가 없습니다.");

                is_possible = is_Continue(false);
		put = false;
		if (is_possible) {
			do{
				insView_->showMessage("");
				insView_->showMessage("Player Two가 놓을 돌의 위치를 입력하시오: (x y)");
				std::tuple<int, int> result = insView_->inputLocation();
				int x = std::get<0>(result) - 1;
				int y = std::get<1>(result) - 1;
				if (x >= 0 and x < size and y >= 0 and y < size) {
					bool is_locatable = is_Possible(x, y, false);
					if (is_locatable) {
						insModel_->setArray(x, y, false);
						put = true;
					}
					else {
						insView_->showMessage("자신과 상대편 돌 사이에만 돌을 놓을 수 있습니다");
					}
				}
				else {
					put = false;
					insView_->showMessage("잘못된 범위의 값을 입력하였습니다.");
					insView_->showMessage("1~"+std::to_string(size)+" 사이의 값을 입력해주세요.");
				}
			} while(!put);
			Reverse(false); // 뒤집을 돌을 찾아줌
			insView_->showArray(insModel_->getArray());
		}
		else 
			insView_->showMessage("Player Two가 놓을 수 있는 위치가 없습니다.");

		if ((is_Continue(true) == false and is_Continue(false) == false) or is_End())
		      is_end = true;	

	}while(!is_end);
	Score();
}

bool Controller::is_Possible(int j, int i, bool is_playerone) {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
	if(is_playerone){
		if(i-2>=0 and j-2>=0){
                        if(arr[i-1][j-1] == "B" and arr[i-2][j-2] == "W")
				//왼쪽 위  대각선
                                return true;
                }
                if(i-2>=0){
                        if(arr[i-1][j] == "B" and arr[i-2][j] == "W")
				//위쪽
                                return true;
                }
                if(i-2>=0 and j+2 <size){
                        if(arr[i-1][j+1] == "B" and arr[i-2][j+2] == "W")
				//오른쪽 위 대각선
                                return true;
                }
                if(j-2>=0){
                        if(arr[i][j-1] == "B" and arr[i][j-2] == "W")
				//왼쪽
                                return true;
                }
		if(i+2<size and j+2<size){
                        if(arr[i+1][j+1] == "B" and arr[i+2][j+2] == "W")
				//오른쪽 아래 대각선
                                return true;
                }
                if(i+2<size){
                        if(arr[i+1][j] == "B" and arr[i+2][j] == "W")
				//아래쪽
                                return true;
                }
                if(i+2<size and j-2 >=0){
                        if(arr[i+1][j-1] == "B" and arr[i+2][j-2] == "W")
				//왼쪽 아래 대각선
                                return true;
                }
                if(j+2<size){
                        if(arr[i][j+1] == "B" and arr[i][j+2] == "W")
				//오른쪽
                                return true;
                }
	}
	else{
                if(i-2>=0 and j-2>=0){
                        if(arr[i-1][j-1] == "W" and arr[i-2][j-2] == "B")
                                //왼쪽 위  대각선
                                return true;
                }
                if(i-2>=0){
                        if(arr[i-1][j] == "W" and arr[i-2][j] == "B")
                                //위쪽
                                return true;
                }
                if(i-2>=0 and j+2 <size){
                        if(arr[i-1][j+1] == "W" and arr[i-2][j+2] == "B")
                                //오른쪽 위 대각선
                                return true;
                }
                if(j-2>=0){
                        if(arr[i][j-1] == "W" and arr[i][j-2] == "B")
                                //왼쪽
                                return true;
                }
                if(i+2<size and j+2<size){
                        if(arr[i+1][j+1] == "W" and arr[i+2][j+2] == "B")
                                //오른쪽 아래 대각선
                                return true;
                }
                if(i+2<size){
                        if(arr[i+1][j] == "W" and arr[i+2][j] == "B")
                                //아래쪽
                                return true;
                }
                if(i+2<size and j-2 >=0){
                        if(arr[i+1][j-1] == "W" and arr[i+2][j-2] == "B")
                                //왼쪽 아래 대각선
                                return true;
                }
                if(j+2<size){
                        if(arr[i][j+1] == "W" and arr[i][j+2] == "B")
                                //오른쪽
                                return true;
                }
        }
	return false;
}

void Controller::Reverse(bool is_playerone) {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        for (int i=0;i<size;i++){
                for( int j=0;j<size;j++){
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
void Controller::is_Reverse(int i, int j, bool is_playerone){
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
	int size = insModel_->getSize();
	if(is_playerone) {
		if(i-1>=0 and j-1>=0 and i+1 < size and j+1 <size){
			if(arr[i-1][j-1] == "W" and arr[i+1][j+1] == "W")
				insModel_->modifyArray(i,j);
		}
		if(i-1>=0 and i+1 < size){
                        if(arr[i-1][j] == "W" and arr[i+1][j] == "W")
                                insModel_->modifyArray(i,j);
		}
	        if(j-1>=0 and j+1 <size){
                        if(arr[i][j-1] == "W" and arr[i][j+1] == "W")
                                insModel_->modifyArray(i,j);
		}
		if(i-1>=0 and j-1>=0 and i+1 < size and j+1 <size){
                        if(arr[i-1][j+1] == "W" and arr[i+1][j-1] == "W")
                                insModel_->modifyArray(i,j);
		}
	} else {
		if(i-1>=0 and j-1>=0 and i+1 < size and j+1 <size){
                        if(arr[i-1][j-1] == "B" and arr[i+1][j+1] == "B")
                                insModel_->modifyArray(i,j);
                }
                if(i-1>=0 and i+1 < size){
                        if(arr[i-1][j] == "B" and arr[i+1][j] == "B")
                                insModel_->modifyArray(i,j);
                }
                if(j-1>=0 and j+1 <size){
                        if(arr[i][j-1] == "B" and arr[i][j+1] == "B")
                                insModel_->modifyArray(i,j);
                }
                if(i-1>=0 and j-1>=0 and i+1 < size and j+1 <size){
                        if(arr[i-1][j+1] == "B" and arr[i+1][j-1] == "B")
                                insModel_->modifyArray(i,j);
                }
	}
}
bool Controller::is_Continue(bool is_playerone) {
	return true;
}

bool Controller::is_End() {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int one_count=0;
        int two_count=0;
        for (int i=0;i<size;i++){
                for( int j=0;j<size;j++){
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
        int size = insModel_->getSize();
	int one_score=0;
	int two_score=0;
	for (int i=0;i<size;i++){
                for( int j=0;j<size;j++){
			if(arr[i][j] == "W")
				one_score += 1;
			if(arr[i][j] == "B")
				two_score += 1;
		}
	}
	insView_->showMessage("Player One의 점수는 " + std::to_string(one_score) +  "입니다.");
	insView_->showMessage("Player Two의 점수는 " + std::to_string(two_score) + "입니다.");
	if (one_score > two_score)
		insView_->showMessage("Player One이 승리했습니다.");
	else
		insView_->showMessage("Player Two가 승리했습니다.");
}
