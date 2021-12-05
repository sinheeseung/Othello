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
	 std::vector<std::vector<std::string>> getArray(); // ���� ���� return
         void setArray(int x, int y, bool is_playone); // �ǿ� ���� ���� �Լ�
         void modifyArray(int x, int y); // ���� ������ �Լ�        
 private:
	 std::vector<std::vector<std::string>> arr_;
};
#endif  // DESKTOP_OTHELLO_MODEL_H_
