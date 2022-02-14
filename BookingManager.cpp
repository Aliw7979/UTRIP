#include"BookingManager.hpp"
using namespace std;
void BookingManager::add_item(string id_init,
                              string hotel_id_init, string room_type_init,
                              int quantity_init, int cost_init,
                              int check_in_init, int check_out_init)
{
    items.push_back(BookedItem(id_init,
                               hotel_id_init, room_type_init,
                               quantity_init, cost_init,
                               check_in_init, check_out_init));
}