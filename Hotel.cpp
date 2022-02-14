#include"Hotel.hpp"
#include<iostream>
#include<iomanip>
using namespace std;

Hotel::Hotel(vector<string> data)
{
    unique_id = data[0];
    name = data[1];
    hotel_star_rating = stoi(data[2]);
    review = data[3];
    facilities = data[4];
    city = data[5];
    latitude = stod(data[6]);
    longitude = stod(data[7]);
    image_url = data[8];
    num_of_standard_rooms = stoi(data[9]);
    num_of_deluxe_rooms = stoi(data[10]);
    num_of_luxury_rooms = stoi(data[11]);
    num_of_premium_rooms = stoi(data[12]);
    standard_room_price = stod(data[13]);
    deluxe_room_price = stod(data[14]);
    luxury_room_price = stod(data[15]);
    premium_room_price = stod(data[16]);
    for (int i = 1; i < num_of_standard_rooms; i++)
    {
        id_of_standard_rooms.push_back("s" + to_string(i));
    }
    for (int i = 1; i < num_of_deluxe_rooms; i++)
    {
        id_of_deluxe_rooms.push_back("d" + to_string(i));
    }
    for (int i = 1; i < num_of_luxury_rooms; i++)
    {
        id_of_luxury_rooms.push_back("l" + to_string(i));
    }
    for (int i = 1; i < num_of_premium_rooms; i++)
    {
        id_of_premium_rooms.push_back("p" + to_string(i));
    }
}
vector<string> Hotel::available_rooms_ids(string type, int check_in, int check_out)
{
    vector<string> ids;
    if (type == "standard")
    {
        for (int i = 0; i < id_of_standard_rooms.size(); i++)
        {
            if (reserve_possibility(id_of_standard_rooms[i], check_in, check_out) == true)
            {
                ids.push_back(id_of_standard_rooms[i]);
            }
        }
    }
    if (type == "deluxe")
    {
        for (int i = 0; i < id_of_deluxe_rooms.size(); i++)
        {
            if (reserve_possibility(id_of_deluxe_rooms[i], check_in, check_out) == true)
            {
                ids.push_back(id_of_deluxe_rooms[i]);
            }
        }
    }
    if (type == "luxury")
    {
        for (int i = 0; i < id_of_luxury_rooms.size(); i++)
        {
            if (reserve_possibility(id_of_luxury_rooms[i], check_in, check_out) == true)
            {
                ids.push_back(id_of_luxury_rooms[i]);
            }
        }
    }
    if (type == "premium")
    {
        for (int i = 0; i < id_of_premium_rooms.size(); i++)
        {
            if (reserve_possibility(id_of_premium_rooms[i], check_in, check_out) == true)
            {
                ids.push_back(id_of_premium_rooms[i]);
            }
        }
    }
    return ids;
}
void Hotel::reserver(string room_type, int quantity, int check_in, int check_out, vector<string> available_rooms, string email)
{
    double cost = cost_of_order(room_type, quantity);
    for (int i = 0; i < quantity; i++)
    {
        add_item(available_rooms[i], unique_id, room_type, quantity, cost, check_in, check_out);
        cout << available_rooms[i] << " ";
    }
    cout << endl;
    return;
}
double Hotel::cost_of_order(string room_type, int quantity)
{
    if (room_type == "standard")
    {
        return quantity * standard_room_price;
    }

    if (room_type == "deluxe")
    {
        return quantity * deluxe_room_price;
    }

    if (room_type == "luxury")
    {
        return quantity * luxury_room_price;
    }

    if (room_type == "premium")
    {
        return quantity * premium_room_price;
    }
    return 0;
}
void Hotel::show_full_information()
{
    cout << unique_id << endl
         << name << endl
         << "star: " << hotel_star_rating << endl
         << "overview: " << review << endl
         << "amenities: " << facilities << endl
         << "city: " << city << endl
         << "latitude: " << fixed << setprecision(2) << latitude << endl
         << "longitude: " << fixed << setprecision(2) << longitude << endl
         << "#room: " << num_of_standard_rooms << " "
         << num_of_deluxe_rooms << " "
         << num_of_luxury_rooms << " "
         << num_of_premium_rooms << endl
         << "price: " << standard_room_price << " "
         << deluxe_room_price << " "
         << luxury_room_price << " "
         << premium_room_price << endl;
}
double Hotel::average_price()
{
    double all_price = standard_room_price + deluxe_room_price + luxury_room_price + premium_room_price;
    int room_model_existance = 0;
    if (num_of_standard_rooms != 0)
        room_model_existance += 1;
    if (num_of_deluxe_rooms != 0)
        room_model_existance += 1;
    if (num_of_luxury_rooms != 0)
        room_model_existance += 1;
    if (num_of_premium_rooms != 0)
        room_model_existance += 1;
    double average = all_price / room_model_existance;
    return average;
}

void Hotel::show_summary()
{
    double average = average_price();
    int total_num_of_rooms = num_of_standard_rooms + num_of_deluxe_rooms + num_of_luxury_rooms + num_of_premium_rooms;
    cout << unique_id << " "
         << name << " "
         << hotel_star_rating << " "
         << city << " "
         << total_num_of_rooms << " "
         << fixed << setprecision(2) << average << endl;
    ;
}
string Hotel::get_id() { return unique_id; }
string Hotel::get_city() { return city; }
int Hotel::get_rating() { return hotel_star_rating; }
bool Hotel::room_reserve_checker(string type, int quantity, int check_in, int check_out)
{
    int counter = 0;
    if (type == "standard")
    {
        if (num_of_standard_rooms >= quantity)
        {
            for (int i = 0; i < id_of_standard_rooms.size(); i++)
            {
                if (reserve_possibility(id_of_standard_rooms[i], check_in, check_out) == true)
                {
                    counter += 1;
                }
            }
            if (counter >= quantity)
            {
                return true;
            }
        }
    }
    if (type == "deluxe")
    {
        if (num_of_deluxe_rooms >= quantity)
        {
            for (int i = 0; i < id_of_deluxe_rooms.size(); i++)
            {
                if (reserve_possibility(id_of_deluxe_rooms[i], check_in, check_out) == true)
                {
                    counter += 1;
                }
            }
            if (counter >= quantity)
            {
                return true;
            }
        }
    }
    if (type == "luxury")
    {
        if (num_of_luxury_rooms >= quantity)
        {
            for (int i = 0; i < id_of_luxury_rooms.size(); i++)
            {
                if (reserve_possibility(id_of_luxury_rooms[i], check_in, check_out) == true)
                {
                    counter += 1;
                }
            }
            if (counter >= quantity)
            {
                return true;
            }
        }
    }
    if (type == "premium")
    {
        if (num_of_premium_rooms >= quantity)
        {
            for (int i = 0; i < id_of_premium_rooms.size(); i++)
            {
                if (reserve_possibility(id_of_premium_rooms[i], check_in, check_out) == true)
                {
                    counter += 1;
                }
            }
            if (counter >= quantity)
            {
                return true;
            }
        }
    }
    return false;
}
bool Hotel::reserve_possibility(string id_of_room, int check_in_test, int check_out_test)
{
    int counter1 = 0, counter2 = 0;
    for (int i = 0; i < items.size(); i++)
    {
        if (id_of_room == items[i].get_id())
        {
            if (items[i].get_check_in() >= check_in_test && items[i].get_check_in() >= check_out_test)
            {
                return false;
            }
        }
    }
    return true;
}

