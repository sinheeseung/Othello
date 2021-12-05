/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#ifndef DESKTOP_OTHELLO_MODEL_H_
#define DESKTOP_OTHELLO_MODEL_H_
#include "controller.h"
#include <vector>
#include <string>

class Model {
 public:
         Model(void);
	 void init(int size);
	 std::vector<std::vector<std::string>> getArray(); // 현재 판을 return
         int getSize();
         void setArray(int x, int y, bool is_playone); // 판에 돌을 놓는 함수
         void modifyArray(int x, int y); // 돌을 뒤집는 함수        
 private:
	 std::vector<std::vector<std::string>> arr_;
         int size_;
};
#endif  // DESKTOP_OTHELLO_MODEL_H_
