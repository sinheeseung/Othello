/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#ifndef DESKTOP_OBJECT_ORIENTED_DESIGN_OTHELLO_MODEL_H_
#define DESKTOP_OBJECT_ORIENTED_DESIGN_OTHELLO_MODEL_H_
#include <vector>
#include <string>
#include "controller.h"
class Model {
 public:
         Model(void);
         void init(int size);
         std::vector<std::vector<std::string>> getArray();
         int getSize();
         void setArray(int x, int y, bool is_playone);
         void modifyArray(int x, int y);
 private:
         std::vector<std::vector<std::string>> arr_;
         int size_;
};
#endif  // DESKTOP_OBJECT_ORIENTED_DESIGN_OTHELLO_MODEL_H_
