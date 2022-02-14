#ifndef FILTER_H
#define FILTER_H "FILTER_H"
#include"Hotel.hpp"

class Filter
{
    public:
    virtual std::vector<Hotel>applier(std::vector<Hotel>&hotels_init)=0;
    void filtered_temp_killer();
    void updater(std::string new_type,int new_quantity,int new_check_in,int new_check_out);
    void updater(std::string city_reinit);
    void updater(int new_max,int new_min);
    void updater(double new_max_price,double new_min_price);
    //virtual void update()=0;
    protected:
    std::vector<Hotel>filtered_hotels;
    std::string chosen_city;
    int max_star;
    int min_star;
    double max_price;
    double min_price;
    std::string type;
    int quantity;
    int check_in;
    int check_out;
    
};
class City : public Filter
{
public:
    City(std::string city);
    std::vector<Hotel> applier(std::vector<Hotel> &hotels_init);
};

class Stars : public Filter
{
public:
    Stars(int max_star_init, int min_star_init);
    std::vector<Hotel> applier(std::vector<Hotel> &hotels_init);
};
class AverageOfPrice : public Filter
{
public:
    AverageOfPrice(double max_price_init, double min_price_init);
    std::vector<Hotel> applier(std::vector<Hotel> &hotels_init);
};
class SpecificRoom : public Filter
{
public:
    SpecificRoom(std::string type, int quantity, int check_in, int check_out);
    std::vector<Hotel> applier(std::vector<Hotel> &hotels_init);
};
#endif