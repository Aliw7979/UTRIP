#ifndef USER_H
#define USER_H "USER_H"
#include"BookingManager.hpp"
class User : public BookingManager
{
public:
    User(std::string id_init, std::string email_init, std::string password_init);
    std::string get_username(); 
    std::string get_email();
    int get_loging_situation();
    std::string get_password();
    double get_credit();
    void logged_out();
    void credit_adder(double amount);
    void show_credit_history(int count);
    void booked_item_data_collector(std::string hotel_id, std::string room_type, int quantity, int check_in, int check_out, double cost);

private:
    std::string username;
    std::string email;
    std::string password;
    double credit;
    std::vector<double> credit_history;
    std::vector<int> used_ids;
    int new_id;
    int login_situation;
};
#endif