#include "model.h"
#include "view.h"

class Controller {
 public:
  Controller();
  void ApplicationRun(); // 처음 오셀로 시작하는 함수
  bool is_Possible(); // 사용자가 위치를 선택했을 때 놓을 수 잇는 위치인지 확인해주는 함수
  bool is_Reverse();// 사용자가 돌을 놓았을 때 뒤집어야 할 돌이 있는지 확인하는 함수
  ???? Reverse(); // 돌을 뒤집는 함수
  bool is_Continue(); //돌을 놓을 수 있는 위치가 있는지 확인하는 함수
  bool is_End(); //어느 한쪽의 돌만 남은 경우
  int Score(); //종료 되었을 때 점수 계산하는 함수
 private:

};

