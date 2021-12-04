#include "contoller.h"
#include <vector>
#include <string>
class View {
 public:
         View(void);
         void showMessage(std::string text);
         int InputArraySize(); // 처음 시작시 판의 크기 입력
         void showArray(vector<vector<std::string>> arr); // 현재 판 출력
         int inputLocation(); // 돌을 놓을 위치 입력

};

