#pragma once

#include "using_headers.h"

using namespace std;

namespace console_restaurant
{
	//������� ��� ����������� ������.
	//"��� �������" ���������� md5 � 
	//������ ��������� �� 16 ��������.
	string password_hash(const string& str);
}