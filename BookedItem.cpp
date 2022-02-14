#include"BookedItem.hpp"
using namespace std;
BookedItem::BookedItem(string id_init,
                       string hotel_id_init, string room_type_init,
                       int quantity_init, int cost_init,
                       int check_in_init, int check_out_init)
{
    id = id_init;
    hotel_id = hotel_id_init;
    room_type = room_type_init;
    quantity = quantity_init;
    cost = cost_init;
    check_in = check_in_init;
    check_out = check_out_init;
}
string BookedItem::get_id() { return id; }
int BookedItem::get_check_in() { return check_in; }