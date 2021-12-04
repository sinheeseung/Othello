#include "contoller.h"
#include <vector>
#include <string>

class Model {
 public:
         Model(int size);
         vector<vector<std::string>> getarray(); // 현재 판을 return
         void setArray(int x, int y, bool is_playone); // 판에 돌을 놓는 함수
         void modifyArray(int x, int y); // 돌을 뒤집는 함수        
 private:
	 vector<vector<std::string>> arr_;
};

