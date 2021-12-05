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
         int InputArraySize(); // ó�� ���۽� ���� ũ�� �Է�
         void showArray(std::vector<std::vector<std::string>> arr); // ���� �� ���
         std::tuple<int,int> inputLocation(); // ���� ���� ��ġ �Է�

};
#endif  // DESKTOP_OTHELLO_VIEW_H_

