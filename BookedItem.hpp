#ifndef BOOKEDITEM_H
#define BOOKEDITEM_H "BOOKEDITEM_H"
#include <string>

class BookedItem
{
public:
    BookedItem(std::string id_init,
               std::string hotel_id_init, std::string room_type_init,
               int quantity_init, int cost_init,
               int check_in_init, int check_out_init);
    std::string get_id();
    int get_check_in();

private:
    std::string id;
    std::string hotel_id;
    std::string room_type;
    int quantity;
    int cost;
    int check_in;
    int check_out;
};
#endif