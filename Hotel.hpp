#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"
#include"BookingManager.hpp"

class Hotel : public BookingManager
{
public:
    Hotel(std::vector<std::string> data);
    std::string get_id();
    std::string get_city();
    int get_rating();
    double cost_of_order(std::string room_type, int quantity);
    void show_summary();
    void show_full_information();
    double average_price();
    bool room_reserve_checker(std::string type, int quantity, int check_in, int check_out);
    void reserver(std::string room_type, int quantity, int check_in, int check_out, std::vector<std::string> available_rooms, std::string email);
    std::vector<std::string> available_rooms_ids(std::string room_type, int check_in, int check_out);

private:
    bool reserve_possibility(std::string id_of_room, int check_in_test, int check_out_test);
    std::string unique_id;
    std::string name;
    int hotel_star_rating;
    std::string review;
    std::string facilities;
    std::string city;
    double latitude;
    double longitude;
    std::string image_url;
    int num_of_standard_rooms;
    int num_of_deluxe_rooms;
    int num_of_luxury_rooms;
    int num_of_premium_rooms;
    std::vector<std::string> id_of_standard_rooms;
    std::vector<std::string> id_of_deluxe_rooms;
    std::vector<std::string> id_of_luxury_rooms;
    std::vector<std::string> id_of_premium_rooms;
    double standard_room_price;
    double deluxe_room_price;
    double luxury_room_price;
    double premium_room_price;
};
#endif