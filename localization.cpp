#include "localization.h"

#include <map>

using namespace std;

namespace console_restaurant
{
	localization_t localization;

	extern vector<string*> roles;

	void sub_init()
	{
		roles =
		{
			&localization.sys_admin,
			&localization.storager,
			&localization.provider,
			&localization.booker,
			&localization.cook,
			&localization.officiant
		};
	}

	void init_rus_localization()
	{
		localization.product_not_valid1 = "������� ";
		localization.product_not_valid2 = " �� �������.";
		localization.dish_not_valid1 = "����� ";
		localization.dish_not_valid2 = " �� �������.";
		localization.user_not_valid1 = "������������ ";
		localization.user_not_valid2 = " �� �������.";
		localization.enter = "������� ";
		localization.login = "�����";
		localization.hello = "������������ ";
		localization.password = "������";
		localization.family = "�������";
		localization.name = "���";
		localization.father_name = "��������";
		localization.role = "����";
		localization.user_not_exits = "������������ � ����� ������� �� ����������.";
		localization.create_new_user_yn = "������� ������ ������������? �������� ��/���";
		localization.y = "�";
		localization.n = "�";
		localization.cant_open_file = "�� ������� ������� ���� ";
		localization.if_guest = "���� ������ ����� ��� �����, �� ������� \"�����\".";
		localization.avable_roles = "��������� ����";
		localization.role_is_not_exits = "����� ���� ����";
		localization.for_unlogin = "��� ������ �� �������� ������� \"unlogin\"";
		localization.for_commands_list = "��� ��������� ������ ������� ������� \"help\"";
		localization.cant_find_command = "�� ������� ����� ��������";
		localization.input_command = "��������";
		localization.wrong_password = "������������ ������";
		localization.wrong_argument_count = "������������ ���������� ����������";
		localization.guest = "�����";

		localization.sys_admin = "��������� �������������";
		localization.storager = "���������";
		localization.provider = "���������";
		localization.booker = "���������";
		localization.cook = "�����";
		localization.officiant = "���������";
		sub_init();
	}

	void init_eng_localization()
	{
		localization.product_not_valid1 = "Product ";
		localization.product_not_valid2 = " not valid.";
		localization.dish_not_valid1 = "Dish ";
		localization.dish_not_valid2 = "  not valid.";
		localization.user_not_valid1 = "User ";
		localization.user_not_valid2 = " not valid.";
		localization.enter = "Enter ";
		localization.login = "login";
		localization.hello = "Hello ";
		localization.password = "password";
		localization.family = "family";
		localization.name = "name";
		localization.father_name = "patronim";//��������
		localization.role = "����";
		localization.user_not_exits = "User with this login is not exits.";
		localization.create_new_user_yn = "Create new user? Enter yes/no";
		localization.y = "y";
		localization.n = "n";
		localization.cant_open_file = "Cant open file ";
		localization.if_guest = "If you needed Enter as guest, input \"guest\"";
		localization.avable_roles = "��������� ����";
		localization.role_is_not_exits = "This role is not exits";
		localization.for_unlogin = "For unlogin input \"unlogin\"";
		localization.for_commands_list = "For watching list of commands input \"help\"";
		localization.cant_find_command = "Cant find command";
		localization.input_command = "command";
		localization.wrong_password = "Wrong password";
		localization.wrong_argument_count = "Wrong argument count";
		localization.guest = "guest";

		localization.sys_admin = "system administrator";
		localization.storager = "storager";
		localization.provider = "provider";
		localization.booker = "booker";
		localization.cook = "cook";
		localization.officiant = "officiant";
		sub_init();
	}
}