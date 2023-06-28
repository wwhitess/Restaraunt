#include "dish.h"
#include "user.h"
#include "localization.h"
#include "data_row.h"
#include "password_hash.h"
#include "file.h"

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

namespace console_restaurant
{
    // ��� ������� - ������ input �� Python.
    // input_thing - ��� ���� � ������� �����������.
    static string input(const string& input_thing)
    {
        cout << localization.enter << input_thing << ":";
        string result;
        while (result.empty())
        {
            getline(cin, result);
        }
        return result;
    }

    // ��������� �� �������� ������������.
    user* current_user = NULL;
    user guest_user = user(string("guest; guest; guest; guest; guest; none"));

    struct role_commands_collection
    {
        string ru_role;     // ���� ��� ������� �����������.
        string eng_role;    // ���� ��� ���������� �����������.

        struct command
        {
            string key;
            typedef void (*func_t)(const vector<string>&);   // ��� ��������� �� �������, ������� �������� ������ ��������� �������.
            func_t func;
            string commentary;
            int arg_target;

            command(const string& key, func_t func, const string& commentary, int arg_target)
            {
                this->key = key;
                this->func = func;
                this->commentary = commentary;
                this->arg_target = arg_target;
            }
        };

        vector<command> commands;

        role_commands_collection(const string& ru, const string& eng, const vector<command>& commands)
        {
            ru_role = ru;
            eng_role = eng;
            this->commands = commands;
        }

        void exec(const string& key_and_args)
        {
            vector<string> data = parse_row(key_and_args, ' ');
            for (command& current_command : commands)
            {
                if (current_command.key == data[0])
                {
                    current_command.func(data);
                    return;
                }
            }
            cout << "������� �� �������!" << endl;
        }
    };

    namespace commands
    {
        void saveOrdersToFile()
        {
            ofstream file("orders.txt");
            if (!file.is_open())
            {
                cout << "������ ��� �������� ����� ��� ���������� �������." << endl;
                return;
            }

            file << "dish;count;status\n";
            for (const auto& order : orders)
            {
                file << order.dish << ";" << order.quantity << ";�����\n";
            }

            file.close();
        }
        void saveProductsToFile()
        {
            ofstream out("products.txt");
            if (!out)
            {
                cout << "���� ���������� ���������" << endl;
                return;
            }

            out << "product;count;price\n";

            for (const auto& pair : products)
            {
                const string& product_name = pair.first;
                const product& prod = pair.second;

                out << product_name << ";" << prod.count << ";" << prod.price << "\n";
            }

            out.close();
        }

        void saveDishes()
        {
            ofstream out("dishes.txt");
            if (out.is_open())
            {
                out << "name;description;gramms;cook_time;price,needed_products\n";
                // ���������� ������ � ������
                for (const auto& dish : dishes)
                {
                    out << dish.name << ';' << dish.description << ';' << dish.gramms << ';' << dish.cook_time << ';' << dish.price << ';';

                    for (const auto& product : dish.needed_products)
                    {
                        out << product.first << ';' << product.second << ';';
                    }

                    out << '\n';
                }

                out.close();
            }
            else
            {
                cout << "������ ��� �������� ����� ��� ���������� ����." << endl;
            }
        }

        // �������� ����.
        void menu(const vector<string>& args)
        {
            string command;
            cout << endl;

            for (const auto& dish : dishes)
            {
                cout << endl;
                cout << "�����: " << dish.name << endl;
                cout << "��������: " << dish.description << endl;
                cout << "������: " << dish.gramms << endl;
                cout << "����� �������������: " << dish.cook_time << endl;
                cout << "����: " << dish.price << endl;

                cout << "������:" << endl;
                for (const auto& product : dish.needed_products)
                {
                    cout << "- " << product.first << ": " << product.second << endl;
                }

                cout << "--------------------------" << endl;
                cout << endl;
            }
        }

        // �������������� ���������.
        void products_imp(const vector<string>& args)
        {
            string product_name;
            int new_count;
            int new_price;

            cout << "������� ��� ��������: ";
            getline(cin, product_name);

            cout << "������� �����������: ";
            cin >> new_count;

            cout << "������� ����: ";
            cin >> new_price;

            auto it = products.find(product_name);
            if (it != products.end())
            {
                it->second.count = new_count;
                it->second.price = new_price;

                // ��������� ��������� � ����
                saveProductsToFile();
            }
            else
            {
                cout << "������� ��������" << endl;
            }
        }

        void show_products(const vector<string>& args) 
        {
            for (const auto& product : products)
            {
                cout << endl;
                cout << "�������: " << product.first << endl;
                cout << "�����������: " << product.second.count << endl;
                cout << "����: " << product.second.price << endl;
                cout << "--------------------------" << endl;
                cout << endl;
            }
        }

        // �������� �������������.
        void users_imp(const vector<string>& args)
        {
            while (true)
            {
                cout << endl;
                string command = input("�������� (edit, list, exit):\n");

                if (command == "edit")
                {
                    string login = input("����� ��� ��� ���������: ");
                    for (user& usr : users)
                    {
                        cout << endl;
                        if (usr.login == login)
                        {
                            usr.role = input("����: ");

                            usr.family = input("�������: ");

                            usr.name = input("���: ");

                            usr.father_name = input("��������: ");

                            usr.password = password_hash(input("����� ������: "));

                            save_users();

                            cout << endl;
                            break;
                        }
                    }
                    if (command != "edit")
                    {
                        cout << "������������ ��������." << endl;
                    }
                }
                else if (command == "list")
                {
                    for (const user& usr : users)
                    {
                        cout << endl;
                        cout << "�����: " << usr.login << endl;
                        cout << "����: " << usr.role << endl;
                        cout << "�������: " << usr.family << endl;
                        cout << "���: " << usr.name << endl;
                        cout << "��������: " << usr.father_name << endl;
                        cout << "������: " << usr.password << endl;
                        cout << "--------------------------" << endl;
                    }
                }
                else if (command == "exit")
                {
                    break;
                }
                else
                {
                    cout << "����� ������� ���. ���������� ��� ���" << endl;
                }
            }
        }
        void menu_imp(const vector <string>& args)
        {
            string dishName;
            cout << "������� �������� �����, ������� �� ������ ���������������: ";
            getline(cin, dishName);

            for (auto& dish : dishes)
            {
                if (dish.name == dishName)
                {
                    cout << "������� ����� ��� �����: ";
                    getline(cin, dish.name);

                    cout << "������� ����� �������� �����: ";
                    getline(cin, dish.description);

                    cout << "������� ����� ���������� �������: ";
                    getline(cin, dish.gramms);

                    cout << "������� ����� ����� �������������: ";
                    getline(cin, dish.cook_time);

                    cout << "������� ����� ����: ";
                    getline(cin, dish.price);

                    dish.needed_products.clear();

                    // ������ ����� ��������
                    string productName;
                    int productCount;
                    while (true)
                    {
                        cout << "������� �������� �������� (��� ������� '�����', ����� ��������� ����): ";
                        getline(cin, productName);
                        if (productName == "�����")
                            break;

                        cout << "������� ���������� ��������: ";
                        cin >> productCount;
                        cin.ignore(); // ������� ����� ����� ���������� �����

                        // ��������� ����� ������� � �����
                        dish.needed_products.insert({ productName, productCount });
                    }

                    saveDishes(); // ��������� ��������� � �����
                    return;
                }
            }
            cout << "����� � �� �������." << endl;
        }
        void add_dish(const vector <string>& args)
        {
            string dishName;
            cout << "������� �������� �����: ";
            getline(cin, dishName);

            // ���������, ���� �� ��� ����� � ����� ���������
            for (const auto& dish : dishes)
            {
                if (dish.name == dishName)
                {
                    cout << "����� ��� ����������." << endl;
                    return;
                }
            }

            string dishDescription;
            cout << "������� �������� �����: ";
            getline(cin, dishDescription);

            string dishGramms;
            cout << "������� ���������� �������: ";
            getline(cin, dishGramms);

            string dishCookTime;
            cout << "������� ����� �������������: ";
            getline(cin, dishCookTime);

            string dishPrice;
            cout << "������� ����: ";
            getline(cin, dishPrice);

            string dishData = dishName + ";" + dishDescription + ";" + dishGramms + ";" + dishCookTime + ";" + dishPrice;

            // ����������� � ������������ �������� � �� ���������� ��� ������ �����
            string productName;
            string productQuantity;

            while (true)
            {
                cout << "������� �������� �������� (��� '�����' ��� ����������): ";
                getline(cin, productName);

                if (productName == "�����")
                {
                    break;
                }

                cout << "������� ���������� ��������: ";
                getline(cin, productQuantity);

                // ��������� ������� � ��� ���������� � ������ ��������� ��� ������ �����
                dishData += ";" + productName + ";" + productQuantity;
            }

            dish newDish(dishData);

            dishes.push_back(newDish);

            saveDishes();

            cout << endl;
        }
        void add_product(const vector <string>& args) 
        {
            string productName;
            cout << "������� �������� ��������: ";
            getline(cin, productName);

            auto it = products.find(productName);
            if (it != products.end())
            {
                cout << "������� ��� ����������." << endl;
            }
            else
            {
                int productCount;
                cout << "������� ���������� ��������: ";
                cin >> productCount;
                cin.ignore(); // ������� ����� ����� ���������� �����

                int addPrice;
                cout << "������� ���� ��������: ";
                cin >> addPrice;
                cin.ignore();

                product newProduct;
                newProduct.count = productCount;
                newProduct.price = addPrice;
                products.insert({ productName, newProduct });
                saveProductsToFile(); // ��������� ��������� � �����
                cout << endl;
            }
        }
        void delete_dish(const vector <string>& args)
        {
            string dishName;
            cout << "������� �������� �����, ������� �� ������ �������: ";
            getline(cin, dishName);

            auto it = find_if(dishes.begin(), dishes.end(), [&dishName](const dish& d) {
                return d.name == dishName;
                });

            if (it != dishes.end())
            {
                dishes.erase(it);
                saveDishes(); // ��������� ��������� � ����
            }
            else
            {
                cout << "����� �� �������." << endl;
            }
        }
        void delete_product(const vector <string>& args)
        {
            string productName;
            cout << "������� �������� ��������, ������� �� ������ �������: ";
            getline(cin, productName);

            auto it = products.find(productName);
            if (it != products.end())
            {
                products.erase(it);
                saveProductsToFile(); // ��������� ��������� � �����
            }
            else
            {
                cout << "������� �� ������." << endl;
            }
        }
        void add_order(const vector<string>& args)
        {
            string dishName;
            cout << "������� �������� �����: ";
            getline(cin, dishName);

            string dishCount;
            cout << "������� �����������: ";
            cin >> dishCount;

            string dishStatus = "�����";

            string orderData = dishName + ";" + dishCount + ";" + dishStatus;

            
            order newOrder(orderData);

            orders.push_back(newOrder);

            saveOrdersToFile();

            cout << endl;
        }
        void view_order(const vector<string>& args)
        {
            if (orders.empty()) {
                cout << "������� ���." << endl;
                return;
            }

            cout << "������ �������:" << endl;
            for (size_t i = 0; i < orders.size(); ++i) {
                cout << "����� #" << (i + 1) << ": " << orders[i].dish << " (����������: " << orders[i].quantity << ")" << " (������: " << orders[i].status << ")" << endl;
            }
        }
    }

    vector<role_commands_collection> role_commands_collections
    {
        //� ���� �������������� � ���� ������� ���������� ��� ������� �������� ��������������
        role_commands_collection("��������� �������������", "system administrator",
        {
            role_commands_collection::command("1", commands::menu, "�������� ����", 0), //All
            role_commands_collection::command("2", commands::add_dish, "���������� �����", 0), //Admin
            role_commands_collection::command("3", commands::menu_imp, "�������������� ����", 0), //Admin
            role_commands_collection::command("4", commands::delete_dish, "�������� �����", 0), //Admin
            role_commands_collection::command("5", commands::show_products, "������� ������ ���������", 0),
            role_commands_collection::command("6", commands::add_product, "���������� ��������", 0), //All
            role_commands_collection::command("7", commands::products_imp, "�������������� ���������", 0), //Admin
            role_commands_collection::command("8", commands::delete_product, "�������� ��������", 0), //Admin
            role_commands_collection::command("9", commands::users_imp, "�������������� � ����� �������������", 0) //Admin
        }),
        role_commands_collection("���������", "storager",
        {
            role_commands_collection::command("1", commands::show_products, "������� ������ ���������", 0),
            role_commands_collection::command("2", commands::add_product, "���������� ��������", 0)
        }),
        role_commands_collection("���������", "provider",
        {
            role_commands_collection::command("1", commands::show_products, "������� ������ ���������", 0)
        }),
        role_commands_collection("���������", "booker",
        {
            role_commands_collection::command("1", commands::show_products, "������� ������ ���������", 0),
            role_commands_collection::command("2", commands::menu, "�������� ����", 0), 
        }),
        role_commands_collection("�����", "guest",
        {
           role_commands_collection::command("1", commands::menu, "�������� ����", 0),
           role_commands_collection::command("2", commands::add_order, "������� �����", 0)
        }),
        role_commands_collection("�����", "cook",
        {
           role_commands_collection::command("1", commands::view_order, "�������� �������", 0)
        }),
        role_commands_collection("��������", "waiter",
        {
            role_commands_collection::command("1", commands::view_order, "�������� �������", 0)
        }),
    };

    void main_loop()
    {
        while (true)
        {
            cout << localization.if_guest << ".\n";
            string login = input(localization.login);
            current_user = nullptr;
            // ���� ������������ � �������� �������
            // ���� �� ������� - �� ������
            for (user& usr : users)
            {
                if (usr.login == login)
                {
                    current_user = &usr;
                    break;
                }
            }
            if (login == "guest" || login == "�����")
            {
                current_user = &guest_user;
            }
            else if (current_user == nullptr)
            {
                cout << localization.user_not_exits << endl;
                string create_new_user_yn = input(localization.create_new_user_yn);
                user new_user;
                new_user.login = login;
                new_user.password = password_hash(input(localization.password));
                new_user.family = input(localization.family);
                new_user.name = input(localization.name);
                new_user.father_name = input(localization.father_name);
                cout << localization.avable_roles << ":\n";
                for (string* role_ptr : roles)
                {
                    cout << *role_ptr << endl;
                }
                // ��������� ����� �������������� ������������ ������ ���, ����� �� ����� �������������� ����.
                // ������� ���� ��� �������� ��� ����������� ������ �� �������� �����.
                bool is_end_of_role_input = false;
                while (true)
                {
                    new_user.role = input(localization.role);
                    for (string* role_ptr : roles)
                    {
                        if (*role_ptr == new_user.role)
                        {
                            is_end_of_role_input = true;
                            break;
                        }
                    }
                    if (is_end_of_role_input)
                    {
                        break;
                    }
                    cout << localization.role_is_not_exits << ".\n";
                }
                // ��������� ������ ������������, ���� ��������� �� ���� � ��������� � ����.
                users.push_back(new_user);
                current_user = &users[users.size() - 1];
                save_users();
            }
            else
            {
                // ��������� �� ���� ������ � �����.
                while (true)
                {
                    string password = password_hash(input(localization.password));
                    if (password != current_user->password)
                    {
                        cout << localization.wrong_password << '!' << endl;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            // ����� ������ ��� ����������� ������ ������������ � �����
            // ��� ������������ � ������� ���������.
            if (current_user->login == "guest")
            {
                cout << localization.hello << localization.guest << '!' << endl;
            }
            else
            {
                cout << localization.hello << current_user->name << '!' << endl;
            }
            cout << localization.for_unlogin << endl;
            cout << localization.for_commands_list << endl;
            // ������ ��� ����� ��������� ������� ��� ���� ����� ������������.
            role_commands_collection* current_role_commands_collection = nullptr;
            for (role_commands_collection& collection : role_commands_collections)
            {
                if (current_user->role == collection.ru_role || current_user->role == collection.eng_role)
                {
                    current_role_commands_collection = &collection;
                    break;
                }
            }
            if (current_role_commands_collection == nullptr)
            {
                cout << "current_role_commands_collection != nullptr" << endl;
                abort();
            }
            while (true)
            {
                string command_key = input(localization.input_command);
                if (command_key == "help")// ����� ������ ��������� ������.
                {
                    for (role_commands_collection::command& command : current_role_commands_collection->commands)
                    {
                        cout << command.key << " - " << command.commentary << endl;
                    }
                }
                else if (command_key == "unlogin")// ����� �� ��������.
                {
                    break;
                }
                else
                {
                    // ������ ���� ������� � ������ ������.
                    // ���� ������� �� �������, �� ����� �� ���� � ��������������.
                    role_commands_collection::command* current_command = nullptr;
                    for (role_commands_collection::command& command : current_role_commands_collection->commands)
                    {
                        if (command.key == command_key)
                        {
                            current_command = &command;
                            break;
                        }
                    }
                    if (current_command == nullptr)
                    {
                        cout << "command not found" << endl;
                        continue;
                    }
                    vector<string> arguments;
                    if (current_command->arg_target == 0)// ���� � ������� �� �������������� ���� ����������.
                    {
                        current_command->func(arguments);
                    }
                    else
                    {
                        // ���� ����������, ������� ��������� ��������.
                        string args = input(localization.wrong_argument_count);
                        arguments = parse_row(args, ' ');
                        if (arguments.size() != current_command->arg_target)
                        {
                            cout << "invalid args" << endl;
                            continue;
                        }
                        current_command->func(arguments);
                    }
                }
            }
        }
    }
}
