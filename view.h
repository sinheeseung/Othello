#include "contoller.h"
#include <vector>
#include <string>
class View {
 public:
         View(void);
         void showMessage(std::string text);
         int InputArraySize(); // ó�� ���۽� ���� ũ�� �Է�
         void showArray(vector<vector<std::string>> arr); // ���� �� ���
         int inputLocation(); // ���� ���� ��ġ �Է�

};

