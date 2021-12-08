/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "controller.h"
#include "model.h"
#include "view.h"

void ApplicationRun();
// game main flow
bool is_Possible();
// Player가 선택한 위치에 돌을 놓을 수 있는지 확인
void Reverse();
// 돌을 뒤집는 함수
bool is_Continue();
// Player가 돌을 놓을 수 있는곳이 있는 지확인
bool is_End();
//종료조건 확인(판에 하나의 돌만 있는 경우)
void Score();
//경기가 종료된 후 점수 계산
std::tuple<int, int> is_Reverse();

int check(int i, int j, int dir, bool is_playerone);

const char* initMessage = "오델로 판의 크기를 입려해주세요.";
const char* infoMessage = "PlayerOne은 'W'를 PlayerTwo는 'B'를 사용합니다.";
const char* sizeErrorMessage = "4~10 사이의 값을 입력 해주세요";
const char* playerone = "Player One이 놓을 돌의 위치를 입력하시오: (x y)";
const char* playertwo = "Player Two가 놓을 돌의 위치를 입력하시오: (x y)";
const char* errormsg1 = "자신과 상대편 돌 사이에만 돌을 놓을 수 있습니다";
const char* errormsg2 = "잘못된 범위의 값을 입력하였습니다.";
const char* errormsg3 = " 사이의 값을 입력해주세요.";
const char* errormsg4 = "Player One이 놓을 수 있는 위치가 없습니다.";
const char* errormsg5 = "Player Two가 놓을 수 있는 위치가 없습니다.";
const char* scoremsg1 = "Player One의 점수는 ";
const char* scoremsg2 = "Player Two의 점수는 ";
const char* win1 = "Player One이 승리했습니다.";
const char* win2 = "Player Two가 승리했습니다.";
const char* draw = "무승부입니다.";


Controller::Controller() {
        insModel_ = new Model();
        insView_ = new View();
}

void Controller::ApplicationRun() {
        int size;
        while (1) {
                insView_->showMessage(initMessage);
                size = insView_->InputArraySize();
                if (10 >= size && size > 3) {
                        break;
                } else {
                        insView_->showMessage(sizeErrorMessage);
                        insView_->showMessage("");
                }
        }
        insModel_->init(size);
        insView_->showArray(insModel_->getArray());
        insView_->showMessage("");
        insView_->showMessage(infoMessage);
        insView_->showMessage("");
        bool is_end = false;
        do {
                //놓을 수 있는 곳이 있는지 확인
                bool is_possible = is_Continue(true);
                bool put = false;
                if (is_possible) {
                        do {
                                insView_->showMessage(playerone);
                                std::tuple<int, int> result =
                                  insView_->inputLocation();
                                int x = std::get<0>(result) - 1;
                                int y = std::get<1>(result) - 1;
                                if (x >= 0 && x < size && y >= 0 && y < size) {
                                        bool is_locatable =
                                          is_Possible(y, x, true, false);
                                        if (is_locatable) {
                                                put = true;
                                        } else {
                                                insView_->showMessage("");
                                                insView_->
                                                  showMessage(errormsg1);
                                                insView_->showMessage("");
                                        }
                                } else {
                                        put = false;
                                        insView_->showMessage("");
                                        insView_->showMessage(errormsg2);
                                        insView_->showMessage("1~"+std::
                                          to_string(size) + errormsg3);
                                        insView_->showMessage("");
                                }
                        } while (!put);
                        insView_->showArray(insModel_->getArray());
                        insView_->showMessage("");
                } else {
                       insView_->showMessage(errormsg4);
                }
                is_possible = is_Continue(false);
                put = false;
                if (is_possible) {
                        do {
                                insView_->showMessage("");
                                insView_->showMessage(playertwo);
                                std::tuple<int, int> result =
                                      insView_->inputLocation();
                                int x = std::get<0>(result) - 1;
                                int y = std::get<1>(result) - 1;
                                if (x >= 0 && x < size && y >= 0 && y < size) {
                                        bool is_locatable =
                                           is_Possible(y, x, false, false);
                                        if (is_locatable) {
                                               put = true;
                                        } else {
                                                insView_->showMessage("");
                                                insView_->
                                                  showMessage(errormsg1);
                                                insView_->showMessage("");
                                        }
                                } else {
                                        put = false;
                                        insView_->showMessage("");
                                        insView_->showMessage(errormsg2);
                                        insView_->showMessage("1~" + std::
                                          to_string(size) + errormsg3);
                                        insView_->showMessage("");
                                }
                        } while (!put);
                        insView_->showArray(insModel_->getArray());
                        insView_->showMessage("");

                } else {
                       insView_->showMessage(errormsg5);
                       is_possible = is_Continue(true);
                       if (!is_possible)  insView_->showMessage(errormsg4);
                }
                if ((is_Continue(true) == false
                      && is_Continue(false) == false) || is_End())
                        is_end = true;
        } while (!is_end);
        Score();
}
int Controller::check(int i, int j, int dir, bool is_playerone) {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int count = 0;
        while (1) {
                std::tuple<int, int> result = is_Reverse(i, j, dir);
                i = std::get<0>(result);
                j = std::get<1>(result);
                if (i < 0 || j < 0 || i >= size || j >= size) return 0;
                if (arr[i][j] == "O") return 0;
                if (is_playerone) {
                        if (arr[i][j] == "B") {
                                count++;
                        } else if (arr[i][j] == "W" && count != 0) {
                                return count;
                        }
                } else {
                        if (arr[i][j] == "W") count++;
                        else if (arr[i][j] == "B" && count != 0) return count;
                }
        }
        return 0;
}
bool Controller::is_Possible(int i, int j, bool is_playerone, bool is_con) {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        bool is_reverse = false;
        if (!is_con && arr[i][j] != "O")
                return is_reverse;
        for (int dir = 0; dir < 8; dir++) {
                int count = check(i, j, dir, is_playerone);
                if (count > 0) {
                        if (!is_con) {
                                insModel_->setArray(i, j, is_playerone);
                                Reverse(i, j, count, dir, is_playerone);
                                is_reverse = true;
                        } else {
                                return true;
                        }
                }
        }
        return is_reverse;
}

void Controller::Reverse(int i, int j, int count, int dir, bool is_playerone) {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int reverse = 0;
        while (reverse < count) {
                std::tuple<int, int> result = is_Reverse(i, j, dir);
                i = std::get<0>(result);
                j = std::get<1>(result);
                insModel_->modifyArray(i, j);
                reverse++;
        }
}
std::tuple<int, int> Controller::is_Reverse(int i, int j, int dir) {
        switch (dir) {
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
        return {i, j};
}
bool Controller::is_Continue(bool is_playerone) {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        bool ret;
        for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                        if (arr[i][j] == "O") {
                                ret = is_Possible(i, j, is_playerone, true);
                                if (ret) {
                                        return true;
                                }
                        }
                }
        }
        return false;
}

bool Controller::is_End() {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int one_count = 0;
        int two_count = 0;
        for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                        if (arr[i][j] == "W")
                                one_count += 1;
                        if (arr[i][j] == "B")
                                two_count += 1;
                }
        }
        if (one_count == 0 || two_count == 0)
                return true;
        else
                return false;
}

void Controller::Score() {
        std::vector<std::vector<std::string>> arr = insModel_->getArray();
        int size = insModel_->getSize();
        int one_score = 0;
        int two_score = 0;
        for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                        if (arr[i][j] == "W")
                                one_score += 1;
                        if (arr[i][j] == "B")
                                two_score += 1;
                }
        }
        insView_->showMessage(scoremsg1 +
                std::to_string(one_score) +  "입니다.");
        insView_->showMessage(scoremsg2 +
                std::to_string(two_score) + "입니다.");
        insView_->showMessage("");
        if (one_score > two_score)
                insView_->showMessage(win1);
        else if (one_score < two_score)
                insView_->showMessage(win2);
        else
                insView_->showMessage(draw);
}
