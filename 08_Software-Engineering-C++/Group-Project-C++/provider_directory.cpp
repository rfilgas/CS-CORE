#include "provider_directory.h"

// assign code, if name exists, store data, if not, create new entry in map.
//provider name, service name, service id, 
int provider_directory::add_entry(string &p_name, string &s_name, float cost){
    /*
    * Adds entry to dir_entry if it exists, otherwise add new dir_entry to entry map
    */
    string empty = ""; //empty string because it will be necessary regardless of find result
    //generate 6 digit code for use in insertion
    string code = "";
    if(top < 100000){ //if top is not 6 digits long
        top += 100001; //force 6 digits
        code = std::to_string(top); //convert to string
        top -= 100000;
        code[0] = '0'; //change first digit to 0
    }
    else{ //if top is already 6 digits long, just convert it to string
        code = std::to_string(top);
        top++;
    }
    auto it = entries.find(p_name); //check if provider exists in directory
    if(it != entries.end()){
        it->second.add(code, cost, s_name); //if so, add an entry to the list
    }
    else{ //otherwise create a new entry and add it to the map
        dir_entry new_entry; 
        new_entry.add(code, cost, s_name);
        new_entry.edit(p_name, empty, -1, empty);
        entries.insert(std::pair<string,dir_entry>(p_name,new_entry));
    }
    names.insert(std::pair<string,string>(code,s_name));
    return 1;
}




//don't assign code, but do overwrite data. Use code to replace entry.
int provider_directory::update_entry(string &p_name, string &s_code, float cost){
    /*
    * Replace entry if found. Returns -1 if entry is not found, returns 1 if entry is found and replaced
    */
    auto it = entries.find(p_name);
    if(it == entries.end()){ //if entry is not found, return failure
        return -1;
    }
    else{ //otherwise if entry is found
        string empty = "";
        return it->second.edit(empty, s_code, cost, empty); //replace cost of service
    }
}




//call clear_services()
int provider_directory::clear_services(string &pname){
    /*
    * Clears services for specified provider
    */
    auto it = entries.find(pname); //get iterator to find item in entries map
    if(it == entries.end()){ //if the object was not found, return failure
        return -1;
    }
    it->second.clear_services(); //otherwise clear services and return success
    return 1;
}




// delete match
int provider_directory::remove_service(string &pname, string &s_name){
    auto it = entries.find(pname); //get iterator to find item in entries map
    if(it == entries.end()){
        return -1;
    }
    else{
        string id = ""; //id placeholder
        for(auto i : names){ //search through list of service codes
            if(i.second == s_name){ //if one is found, assign id to the relevant code
                id = i.first;
            }
        }
        if(id.length() == 0){ //if id was not found, return failure
            return -1;
        }
        it->second.remove_service(id); //remove found service and return success
        return 1;
    }
}




int provider_directory::edit_service_name(string &p_name,  string &s_name, string &s_name_to_save){
    /*
    * Edits a service name of a service. Returns 1 if relevant service was found and updated,
    * returns -1 if relevant service was not found
    */
    auto it = entries.find(p_name); //get the iterator at the provider's name
    if(it == entries.end()){ //if item wasn't found, return failure
        return -1;
    }
    string empty = "";
    string id = ""; //service code placeholder
    for(auto i : names){ //search through list of service codes for relevant match
        if(i.second == s_name){
            id = i.first;
        }
    } 
    if(id.length() == 0){ //if the service name was not found, return failure
        return -1;
    }
    it->second.edit(empty, id, -1, s_name_to_save); //update new service name
    return 1;
}




int provider_directory::edit_service_cost(string &p_name,  string &s_name, float new_cost){
    /*
    * Edits the cost of a passed in service by name. Returns 1 if cost of relevant service was updated, returns -1
    * if service or provider of service was not found. 
    */
            auto it = entries.find(p_name); //get the iterator at the provider's name
    if(it == entries.end()){ //if item wasn't found, return failure
        return -1;
    }
    string empty = "";
    string id = ""; //service code placeholder
    for(auto i : names){ //search through list of service codes for relevant match
        if(i.second == s_name){
            id = i.first;
        }
    } 
    if(id.length() == 0){ //if the service name was not found, return failure
        return -1;
    }
    it->second.edit(empty, id, new_cost, empty); //update new service cost
    return 1;
}




//display services for one provider at request
int provider_directory::display_p_services(string &p_name){
    /*
    * Displays services of provider by name. Returns 1 if provider was found and services displayed, returns -1
    * if the provider was not found.
    */
    auto it = entries.find(p_name);
    if(it == entries.end()){
        return -1;
    }
    it->second.display();
    return 1;
}




int provider_directory::display_all(){
    /*
    * Displays all providers and their respective services. Returns 1 always.
    */
    for(auto i : entries){
        //std::cout << i.first << std::endl;
        i.second.display();
    }
    return 1;
}




int provider_directory::output(ostream & out){
    for(auto i : entries){
        out << i.first << std::endl;
        i.second.output(out);
    }
    return 1;
}




int provider_directory::save(ostream & to_save){
    to_save << std::to_string(top) << " ~ ";
    for(auto i : entries){
        to_save << i.first << " ~ ";
        i.second.save(to_save);
    }
    to_save << " ~~ ";
    for(auto i : names){
        to_save << i.first << " " << i.second << " ~ ";
    }
    to_save << " ~~ ";
    return 1;
}

int provider_directory::load(std::istream & to_load){
    string current_read;
    to_load >> current_read;
    //load top
    top = stoi(current_read);
    //load entries
    while(to_load >> current_read && current_read != "~~"){
        string p_name;
        while(to_load >> current_read && current_read != "~"){
            p_name += current_read + " ";
        }
        p_name[p_name.length()-1] = '\0';
        dir_entry to_add;
        to_add.load(to_load);
        entries.insert(std::pair<string, dir_entry>(p_name, to_add));
    }
    //load names
    while(to_load >> current_read && current_read != "~~"){
        string service_id;
        service_id = current_read;
        string service_name;
        while(to_load >> current_read && current_read != "~"){
            service_name += current_read + " ";
        }
        service_name[service_name.length()-1] = '\0';
        names.insert(std::pair<string, string>(service_id, service_name));
    }
    return 1;
}

float provider_directory::get_cost(string & service_id){
    string s_name = "";
    for(auto i : names){
        if(i.first == service_id){
            s_name = i.second;
            break;
        }
    }
    if(s_name.length() == 0){
        return -1;
    }
    for(auto i: entries){
        if(i.second.get_cost(service_id) != -1){
            return i.second.get_cost(service_id);
        }
    }
    return -1;
} //given a service ID, use the names map to get the name, then the entries map to get the entry. Finally call get cost and return.

//Test code only

// int main(){
//     provider_directory pd;
//     string p_name1 = "John Provider";

//     float cost1 = 25.23;
//     string service1 = "First service";

//     float cost2 = 3984.22;
//     string service2 = "Second service";

//     float cost3 = 4592.325;
//     string service3 = "Third service";
//     if(pd.add_entry(p_name1, service1, cost1) != 1){
//         std::cout << "Adding entry 1 failed" << std::endl;
//     }
//     if(pd.add_entry(p_name1, service2, cost2) != 1){
//         std::cout << "Adding entry 2 failed" << std::endl;
//     }
//     if(pd.add_entry(p_name1, service3, cost3) != 1){
//         std::cout << "Adding entry 3 failed" << std::endl;
//     }

//     string p_name2 = "Johnathon Providington";

//     cost1 = 44.44;
//     service1 = "Fourth service";

//     cost2 = 55.55;
//     service2 = "Fifth service";

//     cost3 = 66.66;
//     service3 = "Sixth service";
//     if(pd.add_entry(p_name2, service1, cost1) != 1){
//         std::cout << "Adding entry 1 failed" << std::endl;
//     }
//     if(pd.add_entry(p_name2, service2, cost2) != 1){
//         std::cout << "Adding entry 2 failed" << std::endl;
//     }
//     if(pd.add_entry(p_name2, service3, cost3) != 1){
//         std::cout << "Adding entry 3 failed" << std::endl;
//     }


//     pd.display_all();
//     string file = "provider_dir.txt";
//     std::ofstream outfile(file);
//     pd.save(outfile);
//     outfile.close();
//     std::cout << "Saved provider directory to disk" << std::endl << std::endl;

//     std::cout << "Loading provider directory from disk" << std::endl << std::endl;
//     provider_directory pd2;
//     std::ifstream infile(file);
//     pd2.load(infile);
//     pd2.display_all();
//     infile.close();
//     return 0;
// }