/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#ifndef DESKTOP_OTHELLO_VIEW_H_
#define DESKTOP_OTHELLO_VIEW_H_
#include "controller.h"
#include <vector>
#include <string>
class View {
 public:
         View(void);
         void showMessage(std::string text);
         int InputArraySize(); // 처음 시작시 판의 크기 입력
         void showArray(std::vector<std::vector<std::string>> arr); // 현재 판 출력
         std::tuple<int,int> inputLocation(); // 돌을 놓을 위치 입력

};
#endif  // DESKTOP_OTHELLO_VIEW_H_

