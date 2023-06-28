#pragma once

#include "using_headers.h"

using namespace std;

namespace console_restaurant
{
	//��� �������� ��� �������� ���� ����� �����������
	struct localization_t
	{
		string product_not_valid1;
		string product_not_valid2;
		string dish_not_valid1;
		string dish_not_valid2;
		string user_not_valid1;
		string user_not_valid2;
		string enter;
		string login;
		string hello;
		string password;
		string family;
		string name;
		string father_name;
		string role;
		string user_not_exits;
		string create_new_user_yn;
		string y;
		string n;
		string cant_open_file;
		string if_guest;
		string avable_roles;
		string role_is_not_exits;
		string for_unlogin;
		string for_commands_list;
		string cant_find_command;
		string input_command;
		string wrong_password;
		string wrong_argument_count;
		string guest;

		string sys_admin;//��������� �������������.
		string storager;//���������.
		string provider;//���������.
		string booker;//���������.
		string cook;//�����.
		string officiant;//���������.

		//������� ���������� ��������������.
		string redact_menu;
		string redact_product;
		string redact_users;

		//������ ���� ��������� ��������� ��� �������.
		string list_menu_message;
	};

	extern localization_t localization;

	//�������������� ������� �����������.
	void init_rus_localization();

	//�������������� ���������� �����������.
	void init_eng_localization();
}