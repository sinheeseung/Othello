#include "contoller.h"
#include <vector>
#include <string>

class Model {
 public:
         Model(int size);
         vector<vector<std::string>> getarray(); // ���� ���� return
         void setArray(int x, int y, bool is_playone); // �ǿ� ���� ���� �Լ�
         void modifyArray(int x, int y); // ���� ������ �Լ�        
 private:
	 vector<vector<std::string>> arr_;
};

