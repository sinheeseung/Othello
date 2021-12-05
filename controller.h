/*!
 *     Copyright:  Copyright (c) 2021, HeeSeung.me
 */
#ifndef DESKTOP_OTHELLO_CONTROLLER_H_
#define DESKTOP_OTHELLO_CNOTROLLER_H_
#pragma once
#include "model.h"
#include "view.h"

class Model;
class View;

class Controller {
 public:
	 Controller();
 	 void ApplicationRun(); // ó�� ������ �����ϴ� �Լ�
	 bool is_Possible(); // ����ڰ� ��ġ�� �������� �� ���� �� �մ� ��ġ���� Ȯ�����ִ� �Լ�
     bool is_Reverse();// ����ڰ� ���� ������ �� ������� �� ���� �ִ��� Ȯ���ϴ� �Լ�
 	 void Reverse(); // ���� ������ �Լ�
 	 bool is_Continue(); //���� ���� �� �ִ� ��ġ�� �ִ��� Ȯ���ϴ� �Լ�
 	 bool is_End(); //��� ������ ���� ���� ���
 	 void Score(); //���� �Ǿ��� �� ���� ����ϴ� �Լ�
 private:
	 Model* insModel_;
	 View* insView_;
};
#endif  // DESKTOP_OTHELLO_CNOTROLLER_H_
