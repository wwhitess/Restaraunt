#pragma once

#include "using_headers.h"

#include<map>

using namespace std;

namespace console_restaurant
{
	//��� map, ��� ���� - ��� �������� ��������, � �������� - ���������� ���������.
	struct product
	{
		int count;
		int price;
	};

	struct dish
	{
		string name;
		string description;
		string gramms;
		string cook_time;
		string price;
		std::map<string, int> needed_products;

		dish(string& data);

		string to_row();
	};

	struct order
	{
		string dish;
		string quantity;
		string status;
	};



	extern vector<order> orders; //������
	extern  std::map<string, product> products;//�������� �� ������.
	extern vector<dish> dishes;//����.

	//������� ��� �������� ��������� �� �����.
	void load_produts();

	//������� ��� �������� ���� �� �����.
	void load_dishes();

	void load_orders();
}