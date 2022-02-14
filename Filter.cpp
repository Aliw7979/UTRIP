#include"Filter.hpp"
using namespace std;
void Filter::filtered_temp_killer()
{
    filtered_hotels.clear();
}

void Filter::updater(int new_max, int new_min)
{
    max_star = new_max;
    min_star = new_min;
}

void Filter::updater(string city_reinit)
{
    chosen_city = city_reinit;
}

void Filter::updater(string new_type, int new_quantity, int new_check_in, int new_check_out)
{
    type = new_type;
    quantity = new_quantity;
    check_in = new_check_in;
    check_out = new_check_out;
}

void Filter::updater(double new_max_price, double new_min_price)
{
    max_price = new_max_price;
    min_price = new_min_price;
}

City::City(string city)
    : Filter()
{
    chosen_city = city;
}
vector<Hotel> City::applier(vector<Hotel> &hotels_init)
{

    for (int i = 0; i < hotels_init.size(); i++)
    {
        if (hotels_init[i].get_city() == chosen_city)
        {
            filtered_hotels.push_back(hotels_init[i]);
        }
    }
    return filtered_hotels;
}

Stars::Stars(int max_star_init, int min_star_init)
    : Filter()
{
    max_star = max_star_init;
    min_star = min_star_init;
}
vector<Hotel> Stars::applier(vector<Hotel> &hotels_init)
{
    for (int i = 0; i < hotels_init.size(); i++)
    {
        if (hotels_init[i].get_rating() >= min_star && max_star >= hotels_init[i].get_rating())
        {
            filtered_hotels.push_back(hotels_init[i]);
        }
    }
    return filtered_hotels;
}

AverageOfPrice::AverageOfPrice(double max_price_init, double min_price_init)
    : Filter()
{
    max_price = max_price_init;
    min_price = min_price_init;
}
vector<Hotel> AverageOfPrice::applier(vector<Hotel> &hotels_init)
{
    for (int i = 0; i < hotels_init.size(); i++)
    {
        if (hotels_init[i].average_price() >= min_price && hotels_init[i].average_price() <= max_price)
        {
            filtered_hotels.push_back(hotels_init[i]);
        }
    }
    return filtered_hotels;
}


SpecificRoom::SpecificRoom(string type_init, int quantity_init, int check_in_init, int check_out_init)
    : Filter()
{
    type = type_init;
    quantity = quantity_init;
    check_in = check_in_init;
    check_out = check_out_init;
}
vector<Hotel> SpecificRoom::applier(vector<Hotel> &hotels_init)
{
    for (int i = 0; i < hotels_init.size(); i++)
    {
        if (hotels_init[i].room_reserve_checker(type, quantity, check_in, check_out) == true)
        {
            filtered_hotels.push_back(hotels_init[i]);
        }
    }
    return filtered_hotels;
}

