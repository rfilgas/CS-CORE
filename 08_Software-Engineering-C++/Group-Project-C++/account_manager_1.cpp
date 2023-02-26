#include "account_manager.h"


// int account_manager::run_member_report(){
//     return -1;
// }

int account_manager::load_program(){
    return -1;
}

int account_manager::login(string &uid){
    auto it = accounts.find(uid);
    if(it != accounts.end()){
        access_level = it->second.get_account_type();
        return access_level;
    }
    return -1;
}

int account_manager::save_program(){
    return -1;
}

int account_manager::logout(){
    access_level = 0;
    return -1;
}