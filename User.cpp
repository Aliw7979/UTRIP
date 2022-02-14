#include"User.hpp"
#include<iostream>
#include"defines.hpp"
using namespace std;

void User::booked_item_data_collector(string hotel_id, string room_type, int quantity, int check_in, int check_out, double cost)
{
    used_ids.push_back(new_id);
    add_item(to_string(new_id), hotel_id, room_type, quantity, cost, check_in, check_out);
    new_id += 1;
}
string User::get_password()
{
    return password;
}
void User::show_credit_history(int count)
{
    for (int i = credit_history.size() - 1; i >= 0 && count != 0; i--, count--)
    {
        cout << credit_history[i] << endl;
    }
}
double User::get_credit()
{
    return credit;
}
void User::credit_adder(double amount)
{
    credit += amount;
    credit_history.push_back(credit);
}

void User::logged_out()
{
    login_situation = LOGGED_OUT;
}
User::User(string username_init, string email_init, string password_init)
{
    username = username_init;
    email = email_init;
    password = password_init;
    credit = 0;
    credit_history.push_back(credit);
    new_id = 1;
    login_situation = LOGGED_IN;
}
string User::get_username() { return username; }
string User::get_email() { return email; }
int User::get_loging_situation() { return login_situation; }
