#include <iostream>
#include "controller.h"
// test
int main(void) {

  Controller* controller = new Controller();
  controller->ApplicationRun();
  delete controller;

  return 0;
}
