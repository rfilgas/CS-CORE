#include "account_object.h"

//Maybe write a copy constructor instead.
int account::add(string &name, string &uid, string &address, string &city, string &state, string &zip){
    //if the data is invalid, return -1
    if(!is_LETTERS(name) || !is_LETTERS(city) || !is_STATE(state) || !is_UID(uid) || !is_ZIP(zip))
        return -1;
    //otherwise assign respective data members
    account::name = name;
    account::UID = uid;
    account::address = address;
    account::city = city;
    account::state = state;
    account::zip_code = zip;
    account_type = 0;
    return 1;
}




int account::save(ostream & to_save){
    to_save << name << " ~ " << address << " ~ " << city << " ~ " << state << " ~ " << UID << " ~ " << zip_code << " ~ " << account_type << " ~ " << status << " ~ ";
    output_services(to_save);
    return 1;
}



int account::load(std::istream & to_load){
    /*
    * Loads data from a file and stores it in account class. Always returns 1
    */
    string current_read; //variable to store current loaded string
    for(int i = 0; i < 9; i++){ //for every variable to update
        while(to_load >> current_read && current_read != "~" && current_read != "~~"){
            switch(i){ //choose between relevant variables based on the index in for loop
                case 0:
                    name += current_read + " "; //append current string to name
                    break;
                case 1:
                    address += current_read + " "; //append current string to address
                    break;
                case 2:
                    city += current_read + " "; //append current string to city
                    break;
                case 3:
                    state = current_read; //set current string to state
                    break;
                case 4:
                    UID = current_read; //set current string to UID
                    break;
                case 5:
                    zip_code = current_read; //set current string to zip
                    break;
                case 6:
                    account_type = std::stoi(current_read); //convert current string to int and set to account type
                    break;
                case 7:
                    status = std::stoi(current_read);
                    break;
                case 8:
                    services.push_back(std::stoi(current_read)); //convert current service number to int and add to vector
            }
        }
    }
    //set final space to null terminator in relevant variables
    name[name.length()-1] = '\0'; 
    address[address.length()-1] = '\0'; 
    city[city.length()-1] = '\0';
    return 1;
}




//  same as add, but won't update if null passed in to field,.
int account::edit(string &name, string &address, string &city, string &state, string &zip){
    if(name.length() != 0 && is_LETTERS(name))
        account::name = name;
    if(address.length() != 0)
        account::address = address;
    if(city.length() != 0 && is_LETTERS(city))
        account::city = city;
    if(state.length() == 2 && is_STATE(state))
        account::state = state;
    if(zip.length() == 5 && is_ZIP(zip))
        account::zip_code = zip;
    return 1;
}


int account::make_provider(){
    account_type = 1;
    return 1;
}

int account::make_manager(){
    account_type = 2;
    return 1;
}


int account::update(account &to_copy){
    name = to_copy.name;
    address = to_copy.address;
    city = to_copy.city;
    state = to_copy.state;
    UID = to_copy.UID;
    zip_code = to_copy.zip_code;
    account_type = to_copy.account_type;
    return 1;
}



int account::copy(account &to_fill){
    to_fill.name = name;
    to_fill.address = address;
    to_fill.city = city;
    to_fill.state = state;
    to_fill.UID = UID;
    to_fill.zip_code = zip_code;
    to_fill.account_type = account_type;
    return 1;
}

 

int account::output(ostream & out){
    out << name << std::endl;
    out << UID << std::endl;
    out << (account_type == 0 ? (status == 1 ? "Active Member" : "Inactive Member") : "Provider") << std::endl; //if account_type is 0, output gets Member, else Provider
    out << address << std::endl;
    out << city << ", " << state << " " << zip_code << std::endl;
    return 1;
}


//output provider name and provider number. Return -1 if not provider.
int account::out_EFT(ostream & out){
    if(account_type == 0)
        return -1;
    out << name << std::endl;
    out << UID << std::endl;
    return 1;
}


int account::display(){
    return output(std::cout);
}



int account::add_service(int to_add){
    services.push_back(to_add);
    return 1;
}



int account::remove_service(int user_choice){
    int current = 0;
    int end = services.size();
    while(current < end && services[current] != user_choice){
        current++;
    }
    if(current < end){
        services.erase(services.begin() + current);
        return 1;
    }
    return -1;
}



// int account::update_service(service_provided & to_save, int user_choice){
//     return 0;
// }



int account::output_services(ostream &out){
    for(uint i = 0; i < services.size(); i++){
        out << services[i] << " ";
    }
    out << "~~ ";
    return 1;
}



// int account::display_services(){
//     return 0;
// } //include an index for them to choose from




bool account::is_provider(){
    return account_type;
}

bool account::member_status(){
    if(is_provider()){
        return true;
    }
    return status;
}

int account::set_member_status(bool status){
    account::status = status;
    return 1;
}

int account::get_account_type(){
    return account_type;
}

// int main()
// {
//     //std::cout << "Creating first account" << std::endl << std::endl;
//     account myaccount;
//     string name = "Bob";
//     string uid = "111111111";
//     string address = "1600 SW Pennsylvania Ave";
//     string city = "Las Vegas";
//     string state = "DC";
//     string zip = "97302";
//     myaccount.add(name, uid, address, city, state, zip);
//     // myaccount.display();
//     //myaccount.make_provider();
//     // std::cout << std::endl <<std::endl;
//     myaccount.display();
//     std::cout << std::endl << "Saving account information to account.txt" << std::endl;
//     std::ofstream out("account.txt");
//     myaccount.save(out);
//     out.close();
//     std::cout << std::endl << "Loading saved file into new account" << std::endl << std::endl;
//     account myaccount2;
//     std::ifstream filein("account.txt");
//     myaccount2.load(filein);
//     myaccount2.display();
//     filein.close();
//     return 0;
// }