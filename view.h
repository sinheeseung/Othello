/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#ifndef DESKTOP_OBJECT_ORIENTED_DESIGN_OTHELLO_VIEW_H_
#define DESKTOP_OBJECT_ORIENTED_DESIGN_OTHELLO_VIEW_H_
#include <vector>
#include <string>
#include <tuple>
#include "controller.h"
class View {
 public:
         View(void);
         void showMessage(std::string text);
         int InputArraySize();
         void showArray(std::vector<std::vector<std::string>> arr);
         std::tuple<int, int> inputLocation();
};
#endif  // DESKTOP_OBJECT_ORIENTED_DESIGN_OTHELLO_VIEW_H_
