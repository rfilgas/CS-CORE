#include "provider_dir_entry.h"

int dir_entry::edit(string & new_name, string & code, float cost_to_save, string & service_name){
    /*
    * Searches for service in list by code and edits the entry if found. Returns 1
    * if entry was edited, and 0 if requested entry to edit was not found
    */
   if(new_name.length() != 0){
       name = new_name;
       if(code.length() == 0 && cost_to_save < 0 && service_name.length() == 0){
           return 1;
       }
   }
   uint end = codes.size();
   uint current = 0;
   while(current < end && code != codes[current]){ //iterate through the list until reaching the end or a match is found
       current++;
   }
   if(current < end){ //if a match was found, copy contents into proper index
        if(cost_to_save >= 0){
            costs[current] = cost_to_save;
        }
        if(service_name.length() != 0){ //only update service name if one was passed in
            services[current] = service_name;
        }
        return 1; //return success
   }
   return -1; //otherwise, if current == end, return failure
}

int dir_entry::add(string & code, float cost_to_save, string & service_name){
    /*
    * Adds code, cost, and service name to the codes, costs, and services
    * vectors.
    */
    if(code.size() == 0 || cost_to_save < 0 || service_name.size() == 0){
        return -1; //if any data members are invalid, return failure
    }
    //otherwise add all items to their respective lists and return success
    codes.push_back(code);
    costs.push_back(cost_to_save);
    services.push_back(service_name);
    return 1;
}

int dir_entry::remove_service(string & code){
    /*
    * Searches through service list and removes service from list if found. Returns 1
    * if item was found and removed, returns -1 if item was not found.
    */
   uint current = 0;
   uint end = codes.size();
   while(current < end && codes[current] != code){ //search through codes until reaching the end or until a match is found
       current++;
   }
   if(current < end){ //if a match is found, remove it and related information, then return success
       codes.erase(codes.begin() + current);
       costs.erase(costs.begin() + current);
       services.erase(services.begin() + current);
       return 1;
   }
   return -1; //if a match is not found, return failure
}

int dir_entry::clear_services(){
    /*
    * Clears all vectors entirely. Always returns 1.
    */
   codes.clear();
   costs.clear();
   services.clear();
    return 1;
}

//this is a tentative test format, will check later for the proper format
int dir_entry::display(){
    /*
    * Displays all items in each list, as well as each entry number. Returns success always.
    */
    // std::cout << name << std::endl;
    // for(uint i = 0; i < codes.size(); i++){
    //     std::cout << "Entry number: " << i + 1 << std::endl;
    //     std::cout << codes[i] << std::endl;
    //     std::cout << costs[i] << std::endl;
    //     std::cout << services[i] << std::endl << std::endl;
    // }
    // return 1;
    return dir_entry::output(std::cout);
}

int dir_entry::save(ostream & to_save){
    /*
    * Loads the ostream object with data from the directory entry's vectors. Returns 1 on success and -1 on failure
    */
   to_save << name << " ~~ ";
   for(uint i=0;i<codes.size();i++){
       //to_export << "Entry number: " << i+1 << std::endl;
       to_save << " ~ " << codes[i] << " ~ " << costs[i] << " ~ " << services[i] << " ~ ";
   }
   to_save << " ~~ ";
   return 1;
}

int dir_entry::load(std::istream & to_load){
    string current_read;
    while(to_load >> current_read && current_read != "~~"){
        name += current_read + " ";
    }
    name[name.length()-1] = '\0';
    while(to_load >> current_read && current_read != "~~"){
        string service;
        for(int i = 0; i < 3; i++){
            service = "";
            while(to_load >> current_read && current_read != "~"){
                switch(i){
                    case 0:
                        codes.push_back(current_read);
                        break;
                    case 1:
                        costs.push_back(stof(current_read));
                        break;
                    case 2:
                        service += current_read + " ";
                }
            }
        }
        services.push_back(service);
    }
    return 1;
}

int dir_entry::output(ostream & to_export){
    /*
    * Streams all items in each list to passed in ostream object for exporting or displaying.
    */
    if(name.length() == 0)
        to_export << "Name field is empty" << std::endl;
    else
        to_export << name << std::endl << std::endl;
    for(uint i = 0; i < codes.size(); i++){
        to_export << "Entry number: " << i + 1 << std::endl;
        to_export << codes[i] << std::endl;
        to_export << costs[i] << std::endl;
        to_export << services[i] << std::endl << std::endl;
    }
    return 1;
}



float dir_entry::get_cost(string &lookup_code){
    int size = codes.size();
    for(int i = 0; i < size; ++i){
        if(codes[i] == lookup_code){
            return costs[i];
        }
    }
    return -1;
}


//Test code only

// int main(){
//     dir_entry dir;
//     string name = "Services provider name";
//     string empty = "";
//     string code = "000000001";
//     float cost = 25.23;
//     string service = "First service";
//     if(dir.edit(name, empty, -1, empty) == 2)
//         std::cout << "Edit name successful" << std::endl;
//     dir.add(code, cost, service);

//     code = "000000002";
//     cost = 3984.22;
//     service = "Second service";
//     dir.add(code, cost, service);

//     code = "000000003";
//     cost = 4592.325;
//     service = "Third service";
//     dir.add(code, cost, service);

//     dir.display();

//     // std::cout << std::endl << "Done with first display" << std::endl << std::endl;

//     // code = "Third code";
//     // cost = 69420.666;
//     // service = "This is an edited service!!!!";
//     // dir.edit(empty, code, cost, service);

//     // dir.display();

//     // std::cout << std::endl << "Done with edited display" << std::endl << std::endl;

//     // dir.remove_service(code);

//     // dir.display();

//     // std::cout << std::endl << "Done with removal" << std::endl << std::endl;

//     string file = "provider_dir.txt";

//     std::ofstream fileout(file);
//     dir.save(fileout);
//     fileout.close();

//     std::cout << "Output saved to " << file << std::endl << std::endl;

//     dir_entry entry2;
//     std::ifstream infile(file);
//     entry2.load(infile);
//     entry2.display();
    
//     return 0;
// }