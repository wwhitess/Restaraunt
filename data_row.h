#pragma once

#include "using_headers.h"

using namespace std;

namespace console_restaurant
{
	//������� ������ �������� ������ � �������.
	int index_of(vector<string>& data, const string& key);

	//������ csv ��� � ������ �����
	vector<string> parse_row(const string& row, char splitter = ';');

	//������ ������ ����� � ������ ��� ������ � ����.
	string to_row(vector<string>& data);

	//� �������� ����� ���� ������ to_row.
	//��� ������������� ��� ����������� ��������� � ������ ��� ������ ������� to_row.
	//�� ������������ ���������� ������ � ������ ��� ������ ������� parse_row, 
	//� ����� ������ ������������ � ���������.
}