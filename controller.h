/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#ifndef DESKTOP_OTHELLO_CONTROLLER_H_
#define DESKTOP_OTHELLO_CNOTROLLER_H_
#pragma once
#include <tuple>
#include "model.h"
#include "view.h"

class Model;
class View;

class Controller {
 public:
         Controller();
         void ApplicationRun();  // game main flow
         bool is_Possible(int i, int j, bool is_playerone, bool is_con);
         // Player가 선택한 위치에 돌을 놓을 수 있는지 확인
         void Reverse(int i, int j, int count, int dir, bool is_playerone);
         // 돌을 뒤집는 함수
         bool is_Continue(bool is_playerone);
         // Player가 돌을 놓을 수 있는곳이 있는 지확인
         bool is_End();
         //종료조건 확인(판에 하나의 돌만 있는 경우)
         int check(int i, int j, int dir, bool is_playerone);
         void Score();
         //경기가 종료된 후 점수 계산
         std::tuple<int, int> is_Reverse(int i, int j, int dir);
 private:
         Model* insModel_;
         View* insView_;
};
#endif  // DESKTOP_OTHELLO_CNOTROLLER_H_
