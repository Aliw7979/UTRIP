#include"HotelsDataManager.hpp"
#include<iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;

HotelsDataManager::HotelsDataManager(string address)
{
    string temp, genre_temp, line, word;
    ;
    ifstream books_file(address);
    books_file.ignore(SKIP_FIRST_LINE, '\n');

    while (getline(books_file, line))
    {
        row.clear();

        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }
        hotels.push_back(Hotel(row));
    }
    sorter(hotels);
}
void HotelsDataManager::hotel_reserver(string hotel_id,string room_type,int quantity,int check_in,int check_out,string email)
{
    Hotel *ph=hotel_finder_by_id(hotel_id);
    User *pu=user_finder_by_email(email);
    if(ph==NULL)
    {
        cout<<"Not Found"<<endl;
        return;
    }
    if(check_in>check_out)
    {
        cout<<"Bad Request"<<endl;
        return;
    }
    vector<string>recieved_ids=ph->available_rooms_ids(room_type,check_in,check_out);
   if(recieved_ids.size()>=quantity)
   {
       if(ph->cost_of_order(room_type,quantity)>pu->get_credit())
       {
           cout<<"Not Enough Credit"<<endl;
           return;
       }
       else
       {
           ph->reserver(room_type,quantity,check_in,check_out,recieved_ids,email);
           pu->booked_item_data_collector(hotel_id,room_type,quantity,check_in,check_out,ph->cost_of_order(room_type,quantity));
           return;
       }
       
   }
   else
   {
       cout<<"Not Enough Room"<<endl;
   }
   
}
int HotelsDataManager::user_log_in_controller(string email,string password)
{
    for(int i=0;users.size();i++)
    {
        if(email==users[i].get_email() && password==users[i].get_password())
        {
            return CORRECT_LOGIN_INFORMATION;
        }
    }
    return INCORRECT_LOGIN_INFORMATION;
}
void HotelsDataManager::delete_all_filters()
{
    for(int i=0;i<filters.size();i++)
    {
        delete filters[i];
    }
    filters.clear();
    filter_update_detector.clear();
    cout<<"OK"<<endl;
}
int HotelsDataManager::duplicate_filter_finder(string type_of_filter)
{
    for(int i=0;i<filter_update_detector.size();i++)
    {
        if(filter_update_detector[i]==type_of_filter)
        {
            return i;
        }
        if(filter_update_detector[i]==type_of_filter)
        {
            return i;
        }
        if(filter_update_detector[i]==type_of_filter)
        {
            return i;
        }
        if(filter_update_detector[i]==type_of_filter)
        {
            return i;
        }
    }
    return NO_DUPLICATE_FILTER_FOUND;
}
void HotelsDataManager::add_city_filter(string chosen_city)
{   
    int check=duplicate_filter_finder("city");
    if(check!=NO_DUPLICATE_FILTER_FOUND)
    {
        filters[check]->updater(chosen_city);
        cout << "OK" << endl;
        return;
    }
    City *city=new City(chosen_city);
    filters.push_back(city);
    filter_update_detector.push_back("city");
    cout << "OK" << endl;
}
void HotelsDataManager::add_stars_filter(int max,int min)
{   
    int check=duplicate_filter_finder("stars");
    if(check!=NO_DUPLICATE_FILTER_FOUND)
    {
        if(max>MAX_STAR || min<MIN_STAR || min>max)
        {
        cout<<"Bad Request"<<endl;
        return;
        }
    
        filters[check]->updater(max,min);
        cout << "OK" << endl;
        return;
    }
    if(max>MAX_STAR || min<MIN_STAR || min>max)
    {
        cout<<"Bad Request"<<endl;
        return;
    }
    cout << "OK" << endl;
    Stars *star = new Stars(max,min);
    filters.push_back(star);
    filter_update_detector.push_back("stars");
}
void HotelsDataManager::add_price_filter(double max,double min)
{   
    int check=duplicate_filter_finder("price");
    if(check!=NO_DUPLICATE_FILTER_FOUND)
    {   
        if(max<min || min<MIN_PRICE || max<MIN_PRICE)
        {
        cout<<"Bad Request"<<endl;
        return;
        }
    
        filters[check]->updater(max,min);
        cout << "OK" << endl;
        return;
    }
    if(max<min || min<MIN_PRICE || max<MIN_PRICE)
    {
        cout<<"Bad Request"<<endl;
        return;
    }
    AverageOfPrice *price=new AverageOfPrice(max,min);
    filters.push_back(price);
    filter_update_detector.push_back("price");
    cout<<"OK"<<endl;
}

void HotelsDataManager::specific_room_filter(string type,int quantity,int check_in,int check_out)
{
    int check=duplicate_filter_finder("specific");
    if(check!=NO_DUPLICATE_FILTER_FOUND)
    {   
        if(quantity<MIN_QUANTITY || check_in>check_out)
        {
        cout<<"Bad Request"<<endl;
        return;
        }
        filters[check]->updater(type,quantity,check_in,check_out);
        cout << "OK" << endl;
        return;
    }
    if(quantity<MIN_QUANTITY || check_in>check_out)
    {
        cout<<"Bad Request"<<endl;
        return;
    }
    SpecificRoom *specific_room=new SpecificRoom(type,quantity,check_in,check_out);
    filters.push_back(specific_room);
    filter_update_detector.push_back("specific");
    cout<<"OK"<<endl;
}


void HotelsDataManager::sorter(vector<Hotel>&a) {
	sort(a.begin(), a.end(), compare_by_alphabet);

}
bool HotelsDataManager:: compare_by_alphabet( Hotel &a, Hotel &b)
{
	return a.get_id() < b.get_id();
}
Hotel *HotelsDataManager::hotel_finder_by_id(string unique_id)
{
    for (int i = 0; i < hotels.size(); i++)
    {
        if (hotels[i].get_id() == unique_id)
        {
            return &hotels[i];
        }
    }
    cout << "Not Found" << endl;
    return NULL;

}
void HotelsDataManager::show_full_hotel_information_by_id(string unique_id)
{
    Hotel *p=hotel_finder_by_id(unique_id);
    if(p==NULL)
    {
        cout<<"Not Found"<<endl;
        return;
    }
    p->show_full_information();
}
void HotelsDataManager::show_hotels_summary()
{
    vector<Hotel>hotels_temp=hotels;
    if(filters.size()!=0)
    {
        for(int i=0;i<filters.size();i++)
        {
            hotels_temp=filters[i]->applier(hotels_temp);
        }
    }
    if(hotels_temp.size()==0)
    {
        cout<<"Empty"<<endl;
        return;
    }
    for (int i = 0; i < hotels_temp.size(); i++)
    {
        hotels_temp[i].show_summary();
    }
    for(int i=0;i<filters.size();i++)
    {
       filters[i]->filtered_temp_killer();
    }
}
User *HotelsDataManager::user_finder_by_username(string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].get_username() == username)
        {
            return &users[i];
        }
    }
}
User *HotelsDataManager::user_finder_by_email(string email)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].get_email() == email)
        {
            return &users[i];
        }
    }
}
void HotelsDataManager::show_credit_history_by_email(string email, int count)
{
    User *p = user_finder_by_email(email);
    p->show_credit_history(count);
}
void HotelsDataManager::money_adder_by_email(string email, double amount)
{
    User *p = user_finder_by_email(email);
    p->credit_adder(amount);
}
void HotelsDataManager::user_exiter(string email)
{
    User *p = user_finder_by_email(email);
    p->logged_out();
}

int HotelsDataManager::register_user(string email, string password, string username)
{
    for (int i = 0; i < users.size(); i++)
    {
        if (username == users[i].get_username())
        {
            return DUPLICATE_INFORMATION;
        }
        else if (email == users[i].get_email())
        {
            return DUPLICATE_INFORMATION;
        }
    }
    users.push_back(User(username, email, password));
    return REGISTER_SUCCSESS;
}

void HotelsDataManager::user_interface()
{

    int user_login_situation = LOGGED_OUT, command_counter = 0,quantity,check_in,check_out;
    vector<string> user_input;
    string all_line, logged_in_email, username, password, logged_in_user = "",room_type;
    while (true)
    {
        user_input.clear();
        all_line.clear();
        getline(cin, all_line);
        string word = "";
        for (auto x : all_line)
        {
            if (x == ' ')
            {

                user_input.push_back(word);
                word = "";
            }
            else
            {
                word = word + x;
            }
        }

        user_input.push_back(word);
        if (user_input[0] == "POST")
        {
            if(user_input[1]=="reserves")
            {
                string hotel_id;
                for(int i=AFTER_QUESTION_MARK;i<user_input.size()-1;i++)
                    {
                        if(user_input[i]=="hotel")
                        {
                            command_counter+=1;
                            hotel_id=user_input[i+1];
                        }
                        if(user_input[i]=="type")
                        {
                            command_counter+=1;
                            room_type=user_input[i+1];
                        }
                        if(user_input[i]=="quantity")
                        {
                            command_counter+=1;
                            quantity=stoi(user_input[i+1]);
                        }
                        if(user_input[i]=="check_in")
                        {
                            command_counter+=1;
                            check_in=stoi(user_input[i+1]);
                        }
                        if(user_input[i]=="check_out")
                        {
                            command_counter+=1;
                            check_out=stoi(user_input[i+1]);
                        }
                    }
                    if(command_counter==RESERVES_CORRECT_INFORMATION)
                        {
                            hotel_reserver(hotel_id,room_type,quantity,check_in,check_out,logged_in_email);
                            command_counter=0;
                            continue;
                        }

            }
            if (user_input[1] == "filters")
            {
                if(user_login_situation==LOGGED_OUT)
                {
                    cout<<"Permission Denied"<<endl;
                    continue;
                }
                if(user_input[AFTER_QUESTION_MARK]=="city")
                {
                    add_city_filter(user_input[4]);
                    continue;
                }
                if(user_input[AFTER_QUESTION_MARK]=="min_star")
                {
                    int min=stoi(user_input[4]);
                    int max=stoi(user_input[6]);
                    add_stars_filter(max,min);
                    continue;
                }
                if(user_input[AFTER_QUESTION_MARK]=="max_star")
                {
                    int max=stoi(user_input[4]);
                    int min=stoi(user_input[6]);
                    add_stars_filter(max,min);
                    continue;
                }
                if(user_input[AFTER_QUESTION_MARK]=="min_price")
                {
                    double min=stod(user_input[4]);
                    double max=stod(user_input[6]);
                    add_price_filter(max,min);
                    continue;
                }
                if(user_input[AFTER_QUESTION_MARK]=="max_price")
                {
                    double max=stod(user_input[4]);
                    double min=stod(user_input[6]);
                    add_price_filter(max,min);
                    continue;
                }
                if(user_input.size()==SPECIFIC_ROOM_FILTER_ENOUGH_INFORMATION)
                {
                    for(int i=AFTER_QUESTION_MARK;i<user_input.size()-1;i++)
                    {
                        if(user_input[i]=="type")
                        {
                            command_counter+=1;
                            room_type=user_input[i+1];
                        }
                        if(user_input[i]=="quantity")
                        {
                            command_counter+=1;
                            quantity=stoi(user_input[i+1]);
                        }
                        if(user_input[i]=="check_in")
                        {
                            command_counter+=1;
                            check_in=stoi(user_input[i+1]);
                        }
                        if(user_input[i]=="check_out")
                        {
                            command_counter+=1;
                            check_out=stoi(user_input[i+1]);
                        
                        }
                        
                    }
                    if(command_counter==SPECIFIC_ROOM_FILTER_CORRECT_INFORMATION)
                        {
                            specific_room_filter(room_type,quantity,check_in,check_out);
                            command_counter=0;
                            continue;
                        }
                    else
                    {
                        cout<<"Bad Request"<<endl;
                    }
                }


            }
            if(user_input[1]=="login")
            {
                int check;
                string email;
                string password;
                for(int i=AFTER_QUESTION_MARK;i<user_input.size()-1;i++)
                {
                    if(user_input[i]=="email")
                    {
                        email=user_input[i+1];
                        command_counter+=1;
                    }
                    if(user_input[i]=="password")
                    {
                        email=user_input[i+1];
                        command_counter+=1;
                    }
                }
                if(command_counter==2)
                {
                    check=user_log_in_controller(email,password);
                if(check==CORRECT_LOGIN_INFORMATION)
                {
                    user_login_situation=LOGGED_IN;
                    logged_in_email=email;
                    continue;
                }
                    command_counter=0;
                }
                
            }
            if (user_input[1] == "logout")
            {
                if(user_login_situation==LOGGED_IN)
                {
                    cout<<"Permission Denied"<<endl;
                    continue;
                }
                user_login_situation = LOGGED_OUT;
                user_exiter(logged_in_email);
                logged_in_email = "";
                delete_all_filters();
                cout << "OK" << endl;
                continue;
            }
            if (user_input[1] == "signup")
            {
                string email;
                for (int i = AFTER_QUESTION_MARK; i < 8; i++)
                {
                    if (user_input[i] == "email")
                    {
                        email = user_input[i + 1];
                        command_counter += 1;
                    }

                    if (user_input[i] == "password")
                    {
                        password = user_input[i + 1];
                        command_counter += 1;
                    }

                    if (user_input[i] == "username")
                    {
                        username = user_input[i + 1];
                        command_counter += 1;
                    }
                    
                }
                if (command_counter == CORRECT_SIGN_INFORMATION)
                {
                    command_counter = 0;
                    int register_status = register_user(email, password, username);
                    if (register_status == DUPLICATE_INFORMATION)
                    {
                        cout << "Bad Request" << endl;
                        continue;
                    }
                    else if (register_status == REGISTER_SUCCSESS)
                    {
                        cout << "OK" << endl;
                        logged_in_email = email;
                        user_login_situation = LOGGED_IN;
                        continue;
                    }
                }
                else
                {
                    cout << "Bad Request" << endl;
                    command_counter = 0;
                }
            }

            if (user_input[1] == "wallet")
            {

                if (user_login_situation == LOGGED_OUT)
                {
                    cout << "Permission Denied" << endl;
                    continue;
                }
                if (user_input[AFTER_QUESTION_MARK] == "amount")
                {
                    double amount = stod(user_input[4]);
                    if (amount <= 0)
                    {
                        cout << "Bad Request" << endl;
                        continue;
                    }
                    money_adder_by_email(logged_in_email, amount);
                    cout << "OK" << endl;
                    continue;
                }
                else
                {
                    cout << "Bad Request" << endl;
                    continue;
                }
            }
            else
            {
                cout << "Not Found" << endl;
            }
        }
        else if (user_input[0] == "GET")
        {
            if (user_login_situation == LOGGED_OUT)
            {
                cout << "Permission Denied" << endl;
                continue;
            }
            if (user_input[1] == "wallet")
            {
                if (user_input.size() != 5)
                {
                    cout << "Bad Request" << endl;
                    continue;
                }
                if (user_input[AFTER_QUESTION_MARK] == "count")
                {
                    show_credit_history_by_email(logged_in_email, stoi(user_input[4]));
                }
                else
                {
                    cout << "Bad Request" << endl;
                    continue;
                }
            }
            if (user_input[1] == "hotels" && user_input.size()==2)
            {
                if (hotels.size() == 0)
                {
                    cout << "Empty" << endl;
                    continue;
                }
                show_hotels_summary();
            }
            if (user_input[1] == "hotels" && user_input.size()==5)
            {
                show_full_hotel_information_by_id(user_input[4]);
                continue;
            }
        }
        else if(user_input[0] == "DELETE")
        {
            if(user_input[1]=="filters")
            {
                delete_all_filters();
                continue;
            }
        }
        else
        {
            cout << "Bad Request" << endl;
        }
    }
}
void HotelsDataManager::print_specific_hotel(string id)
{
    for (int i = 0; i < hotels.size(); i++)
    {
        if (hotels[i].get_id() == id)
        {
            cout << endl
                 << hotels[i].get_id() << endl;
        }
    }
}