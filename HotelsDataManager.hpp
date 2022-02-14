#ifndef HOTELSDATAMANAGER_H
#define HOTELSDATAMANAGER_H "HOTELSDATAMANAGER_H"

#include<string>
#include<vector>
#include"defines.hpp"
#include"Hotel.hpp"
#include"User.hpp"
#include"Filter.hpp"

class HotelsDataManager
{
public:
    HotelsDataManager(std::string address);
    void print_specific_hotel(std::string id);
    void user_interface();
    void show_full_hotel_information_by_id(std::string username);
    void show_hotels_summary();
    int user_log_in_controller(std::string email,std::string password);
    void hotel_reserver(std::string hotel_id,std::string room_type,int quantity,int check_in,int check_out,std::string email);

private:
    int register_user(std::string email, std::string password, std::string username);
    void user_exiter(std::string email);
    void money_adder_by_email(std::string email, double amount);
    void show_credit_history_by_email(std::string email, int count);
    User *user_finder_by_username(std::string username);
    User *user_finder_by_email(std::string email);
    Hotel* hotel_finder_by_id(std::string unique_id);
    bool static compare_by_alphabet(Hotel &a, Hotel &b);
    void sorter(std::vector<Hotel>&a);
    void add_city_filter(std::string chosen_city);
    void add_stars_filter(int max,int min);
    void add_price_filter(double max,double min);
    void specific_room_filter(std::string type,int quantity,int check_in,int check_out);
    int duplicate_filter_finder(std::string type_of_filter);
    void delete_all_filters();
    std::vector<std::string> row;
    std::vector<Hotel> hotels;
    std::vector<User> users;
    std::vector<Filter*>filters;
    std::vector<std::string>filter_update_detector;
};
#endif