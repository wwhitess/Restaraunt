#include "dish.h"
#include "data_row.h"
#include "using_headers.h"
#include "file.h"
#include "localization.h"

using namespace std;

namespace console_restaurant
{
	//������ ��� ��������� ���������� �������� �� �������.
	#define NEXT_PARSED_DATA parsed_data[parsed_data_index++]

	dish::dish(string& data)
	{
		vector<string> parsed_data = parse_row(data);
		//�������� �� ���������� �����.
		//� ����� ���� ��������, � ����� ������� ���� 
		//�������� � ���������� ����������� ���������.
		//������������� ����������� ���������� � ���������� ������� 
		//������ ���� ������ ��� ����� 3 �
		//���������� �� ������ ���� ������.
		if (parsed_data.size() < 7 ||
			parsed_data.size() % 2 == 0)
		{
			cout 
				<< localization.dish_not_valid1
				<< data
				<< localization.dish_not_valid2
				<< endl;
			abort();
		}
		int parsed_data_index = 0;
		name = NEXT_PARSED_DATA;
		description = NEXT_PARSED_DATA;
		gramms = NEXT_PARSED_DATA;
		cook_time = NEXT_PARSED_DATA;
		price = NEXT_PARSED_DATA;
		while (parsed_data_index != parsed_data.size())//���������� �������� � ������� - ��� ����������� ��� ������.
		{
			string product_name = NEXT_PARSED_DATA;
			int product_count = atoi(NEXT_PARSED_DATA.c_str());
			needed_products.insert
			(
				pair<string, int>(product_name, product_count)
			);
		}
	}

	string dish::to_row()
	{
		string result;
		result += name;
		result += ';';
		result += description;
		result += ';';
		result += gramms;
		result += ';';
		result += cook_time;
		result += ';';
		result +=price;
		result += ';';

		map<string, int>::iterator it;

		for (it = needed_products.begin(); it != needed_products.end(); it++)
		{
			result += it->first;
			result += ';';
			result += std::to_string(it->second);
			result += ';';
		}

		result.resize(result.size() - 1);
		return result;
	}

	void load_produts()
	{
		string line;    //������� ������ ��� �����.
		string header;	//������ "������������" ������ �� ����� ������� � ����� ��������. ����� �� ������������.

		ifstream in = nopen_ifile("products.txt");
		getline(in, header);
		while (getline(in, line))
		{
			vector<string> parsed_data = parse_row(line);
			//� �������� ���� ������ 2 ���� - �������� � ���������� � ����.
			//���� ������� ������ ����� ������ ��� ������ 3, �� ��� �� �������� �����.
			if (parsed_data.size() != 3)
			{
				cout
					<< localization.product_not_valid1
					<< line
					<< localization.product_not_valid2
					<< endl;
				abort();
			}
			string product_name = parsed_data[0];
			product prod;
			prod.count = atoi(parsed_data[1].c_str());
			prod.price = atoi(parsed_data[2].c_str());
			products.insert
			(
				{ product_name, prod }
			);
		}
	}

	void load_dishes()
	{
		string line;    //������� ������ ��� �����.
		string header;	//������ "������������" ������ �� ����� ������� � ����� ����. ����� �� ������������.

		ifstream in = nopen_ifile("dishes.txt");
		getline(in, header);
		while (getline(in, line))
		{
			dishes.push_back(dish(line));//��������� ������ ������� �� �����.
		}
	}

	void load_orders()
	{
		string line;    //������� ������ ��� �����.
		string header;	//������ "������������" ������ �� ����� ������� � ����� order. ����� �� ������������.

		ifstream in = nopen_ifile("orders.txt");
		getline(in, header);
		while (getline(in, line))
		{
			orders.push_back(order(line));//��������� ������ orders �� �����.
		}
	}

	vector<order> orders;
	map<string, product> products;
	vector<dish> dishes;
}