#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H "BOOKINGMANAGER_H"

#include"BookedItem.hpp"
#include<vector>
class BookingManager
{
public:
    void add_item(std::string id_init,
                  std::string hotel_id_init, std::string room_type_init,
                  int quantity_init, int cost_init,
                  int check_in_init, int check_out_init);
    void delete_item(std::string id);

protected:
    std::vector<BookedItem> items;
};
#endif