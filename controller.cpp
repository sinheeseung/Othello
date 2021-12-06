#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "controller.h"
#include "model.h"
#include "view.h"

void ApplicationRun(); // game main flow
bool is_Possible(); // Player가 선택한 위치에 돌을 놓을 수 있는지 확인
void Reverse(int i, int j, int count, int dir, bool is_playerone); // 돌을 뒤집는 함수
bool is_Continue(); // Player가 돌을 놓을 수 있는곳이 있는 지확인
bool is_End(); //종료조건 확인(판에 하나의 돌만 있는 경우)
void Score(); //경기가 종료된 후 점수 계산
void is_Reverse(int i, int j, bool is_playerone);
int check(int i, int j, int dir, bool is_playerone);

Controller::Controller() {
        insModel_ = new Model();
        insView_ = new View();
}

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
                                if (x >= 0 && x < size && y >= 0 && y < size) {
                                        bool is_locatable = is_Possible(x, y, true);
                                        if (is_locatable) {
                                                //insModel_->setArray(x, y, true);
                                                put = true;
                                        } else {
                                                insView_->showMessage("자신과 상대편 돌 사이에만 돌을 놓을 수 있습니다");
                                        }
                                } else {
                                        put = false;
                                        insView_->showMessage("잘못된 범위의 값을 입력하였습니다.");
                                        insView_->showMessage("1~"+std::to_string(size)+" 사이의 값을 입력해주세요.");
                                }
                        } while(!put);
                        //Reverse(true); // 뒤집을 돌을 찾아줌
                        insView_->showArray(insModel_->getArray());
                } else 
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
                                if (x >= 0 && x < size && y >= 0 && y < size) {
                                        bool is_locatable = is_Possible(x, y, false);
                                        if (is_locatable) {
                                                //insModel_->setArray(x, y, false);
                                                put = true;
                                        } else {
                                                insView_->showMessage("자신과 상대편 돌 사이에만 돌을 놓을 수 있습니다");
                                        }
                                }
                                else {
                                        put = false;
                                        insView_->showMessage("잘못된 범위의 값을 입력하였습니다.");
                                        insView_->showMessage("1~"+std::to_string(size)+" 사이의 값을 입력해주세요.");
                                }
                        } while(!put);
                        //Reverse(false); // 뒤집을 돌을 찾아줌
                        insView_->showArray(insModel_->getArray());
                } else 
                        insView_->showMessage("Player Two가 놓을 수 있는 위치가 없습니다.");

                if ((is_Continue(true) == false && is_Continue(false) == false) or is_End())
                        is_end = true;	

        } while(!is_end);
        Score();
}
int Controller::check(int j, int i, int dir, bool is_playerone) {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int count = 0;
        while(1) {
                switch (dir)
                {
                case 0:
                //왼쪽 위
                        j--;
                        i--;
                        break;
                case 1:
                // 위
                        i--;
                        break;
                case 2:
                //오른쪽 위
                        j++;
                        i--;
                        break;
                case 3:
                // 왼쪽
                        j--;
                        break;
                case 4:
                //오른쪽
                        j++;
                        break;
                case 5:
                //왼족 아래
                        j--;
                        i++;
                        break;
                case 6:
                //아래
                        i++;
                        break;
                case 7:
                //오른쪽 아래
                        j++;
                        i++;
                        break;     
                default:
                        break;
                }
                if (i < 0 || j < 0 || i >= size || j >= size) break;
                if (arr[i][j] == "O") break;
                if (is_playerone) {
                        if(arr[i][j] == "B"){
                                count++;
                        }
                        else if(arr[i][j] == "W" && count != 0) {
                                return count;
                        }
                } else {
                        if(arr[i][j] == "W") count++;
                        else if(arr[i][j] == "B" && count != 0) return count;
                }
        }
        return 0;
}
bool Controller::is_Possible(int j, int i, bool is_playerone) {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        if (arr[i][j] != "O") return false;
        
	
        for (int dir = 0; dir < 8; dir++) {
                int count = check(j, i, dir, is_playerone);
                if (count > 0) {
                        insModel_->setArray(j, i, is_playerone);
                        Reverse(j, i, count, dir, is_playerone);
                        return true;
                }
        }
        return false;
}

void Controller::Reverse(int j, int i, int count, int dir, bool is_playerone) {
	std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int reverse = 0;
        while(reverse < count) {
                switch (dir)
                {
                case 0:
                //왼쪽 위
                        j--;
                        i--;
                        break;
                case 1:
                // 위
                        i--;
                        break;
                case 2:
                //오른쪽 위
                        j++;
                        i--;
                        break;
                case 3:
                // 왼쪽
                        j--;
                        break;
                case 4:
                //오른쪽
                        j++;
                        break;
                case 5:
                //왼족 아래
                        j--;
                        i++;
                        break;
                case 6:
                //아래
                        i++;
                        break;
                case 7:
                //오른쪽 아래
                        j++;
                        i++;
                        break;     
                default:
                        break;
                }
                insModel_->modifyArray(i,j);
                reverse++;
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
