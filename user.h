#pragma once

#include "using_headers.h"

using namespace std;

namespace console_restaurant
{
    struct user
    {
        string role;        //����
        string family;      //�������
        string name;        //���
        string father_name; //��������
        string login;       //�����
        string password;    //��� ������

        user() = default;

        user(const string& data);

        //���������� ������������ � ������ ��� ������.
        string to_row();
    };

    extern vector<user> users;

    extern vector<string*> roles;//���������������� � localization.cpp

    //������� ��� �������� ������������� �� �����.
    void load_users();

    void save_users();
}